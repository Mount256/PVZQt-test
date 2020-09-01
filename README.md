#植物大战僵尸Qt版
## 一、初步设计
### 1. 框架
本程序分为两个部分：菜单界面采用`QWidget`实现，有一个父窗口，通过信号槽机制调用各种子窗口；游戏界面使用`QGraphicsScene`框架实现，里面包含`view`和各种图形项`item`。

本程序采用面向对象程序设计思路，创建基类植物`Plant`、僵尸`Zombie`、卡牌`Cards`，在这基础上派生出不同的类，如豌豆射手、路障僵尸等。创建一个`Map`类，用以记录植物的位置，以及是否可以种植。

### 2. 界面
首先，整个窗口界面是`900X600`的大小，并且大小不可调。

菜单界面依然是植物大战僵尸的那个味道，放置熟悉的菜单背景，在右侧放置游戏开始按钮，玩家点击后程序会展示僵尸的一封信，再次点击即可进入游戏界面。

游戏界面也依然是植物大战僵尸的那个味道，几乎差不多。最上方是卡牌选择框，在选择框左侧显示阳光点数。左上角是返回菜单和游戏暂停按钮，在左侧摆放割草机，右侧出僵尸，正中一大片区域放植物，最下方展示游戏目标。

游戏开始，依然是植物大战僵尸的味道。玩家选择卡牌，在地图中央点击放置植物；若想铲除植物，则需点击右上方的铲子进行铲除操作。

### 3. 图形项Item
基于`QGraphicsItem`的`Plant`和`Zombie`包含以下函数，注意，前两个是必须要实现的：

```
boundingRect()  // Item的绘制边界
paint()  // Item的绘制
collidesWithItem()  //Item的碰撞判定
advance()  // Item的动作状态
```
因为每种植物和僵尸的动作特点不同，实际编写程序的时候，是需要重写这四个函数的。

可点击的图形项：例如基于`QGraphicsItem`的`Cards`和`Sun`（阳光点数）包含以下函数：
```
boundingRect()  // Item的绘制边界
paint()  // Item的绘制
collidesWithItem()  //Item的碰撞判定
advance()  // Item的动作状态
mousePressEvent() // 鼠标动作
```

想实现各种`Item`的动画效果，就要将定时器`Timer`绑定到`QGraphicsScene`的`advance`函数。同时，游戏生成僵尸的函数也需要绑定到`advance`函数。

## 二、详细设计

### 1. 地图Map
`Map`类是整个程序的核心部位，是重中之重，`Map`主要完成了以下几件事情：
 - 界定地图边界
 - 计算并存储植物的位置
 - 接收玩家的点击事件（尤其是卡牌被点击后）
 - 生成太阳
 
 我们来看看Map的变量：
 

```cpp
static Cards *PreparedPlant; //记录玩家点击了哪张卡牌
static Plant *PlantMap[9][5]; //记录植物的位置，类型是Plant，一般情况下为nullptr
```

地图是如何响应玩家的点击事件的呢？正常情况下，玩家点击地图是没有反应的；但是如果玩家先前点击卡牌购买植物，再点击地图，那么就必须做出反应了：

```cpp
    if(PreparedPlant && event->button()==Qt::LeftButton)
    {
        Shovel::isMovePlant = 0;
        int i = ((int)event->scenePos().x() - 250) / 80;
        int j = ((int)event->scenePos().y() - 100) / 90;
        if(i == 9) --i;  if(j == 5) --j;
        qDebug()<< i << j; //以上都是计算准备种植的位置
        if(!PlantMap[i][j]) // 如果这个位置没被其他植物占用
        {
            QPointF plantPos(290+80*i, 145+90*j);
            switch(PreparedPlant->No)//根据卡牌序号，生成新的植物对象
            {
            case 0: PlantMap[i][j] = new Sunflower(plantPos); break;
            case 1: PlantMap[i][j] = new Peashooter(plantPos); break;
           ........................
            default: break;
            }
            PlantMap[i][j]->setZValue(j);
            scene()->addItem(PlantMap[i][j]);
            PreparedPlant->isPlanted = 1; //告诉卡牌我已经被种植了，意味着可以开始你的冷却动画了
            PreparedPlant->counter = 0; //开始进行冷却等待
            PreparedPlant->StartMode = 0;
            PreparedPlant->sunTotal -= PreparedPlant->sunNeed;
            PreparedPlant = nullptr; //记录准备植物的变量清空，等待下一次卡牌被点击时被赋予新的值
            QApplication::restoreOverrideCursor(); //光标出栈，恢复光标形状
        }    
    }
```
其实铲子的功能也是同样的原理，这里不说了。
### 2. 卡牌Cards
`Cards`主要完成的任务有：

 - 显示卡牌的各种状态
 - 判断并接收玩家的点击事件，并改变光标形状
 - 存储玩家的阳光点数
基类`Cards`包含以下变量：

```
  int No, sunNeed;// 植物编号；植物所需的阳光点数
  int counter; // 计时器，
  int coolTime; // 冷却时间
  QString name; // 植物名字
  bool isPlanted, StartMode; // 记录是否被种植；记录是否是游戏开始，这个是干嘛的后面再说
  static int sunTotal; // 玩家现有的阳光点数,静态成员变量
  
```
paint函数实现了卡牌绘制和冷却效果：

```cpp
void Cards::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QImage image(":/graphics/Cards/card_" + name.toLower() + ".png");
    painter->drawImage(boundingRect(), image); //画出卡牌
    if(sunTotal < sunNeed) //情况一：当阳光点数不足以购买植物时，画禁止点击的矩形
    {
        painter->setBrush(QColor(128, 128, 0, 200));
        painter->drawRect(boundingRect());
    }
    if(counter < coolTime && !StartMode && isPlanted) //情况二：未到冷却时间，画冷却效果
    // 注意，游戏开始时不需要冷却效果，如果没有StartMode来判断游戏是否开始，那游戏一开始就会跑冷却效果，就没法购买植物了；同时，要真的种了植物才能跑冷却，如果没有种不需要冷却效果
    {
        painter->setBrush(QColor(0, 0, 0, 200));
        painter->drawRect(QRectF(425+60*No, 10, 50, 70*(1-qreal(counter)/coolTime)));
    }
}
```
这个函数实现了鼠标点击事件：

```cpp
void Cards::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton) //如果卡牌被点击
    { //如果阳光足够，且已达到冷却时间
        if(sunTotal >= sunNeed && (counter == coolTime || StartMode)){
            QCursor cursor(QPixmap(":/graphics/Plants/" + name + "/0.gif"));//改变鼠标光标为对应植物光标
            QApplication::setOverrideCursor(cursor);
            Map::PreparedPlant = this;//告诉地图，我接下来可能要种植这株植物了
        }
    }
}
```
最后，派生类继承了这些函数，并初始化自己的变量，例如：

```cpp
sunflower::sunflower()
{
    name = "SunFlower"; coolTime = 227; No = 0;
    sunNeed = 50; tip = "向日葵(50)";
}
```

### 3. 植物Plant
基类`Plant`包含以下变量：

```
enum { Type = UserType + 1}; //植物类型记作1
 int HP; //血量
 int ATK; //攻击力
 int posX, posY; //位置
 QString name; //植物名字
 QMovie *movie; //动画
```
基类`Plant`包含以下函数（前三个之前说过，不说了）：

```
 QRectF boundingRect() const;
 void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
 void advance(int phase);
 int type() const; // 返回类型，这个作用就是，
 // 是植物的就返回植物类型（记作1），是僵尸的就返回僵尸类型（记作2），以此类推
```

为什么没有`collidesWithItem()`？因为大部分植物的确不需要碰撞检测，一般碰撞发出者是僵尸。比如向日葵、豌豆射手是不需要碰撞检测的，但是樱桃炸弹、土豆地雷这些是需要的，因为它是碰撞发出者。

以下两个成员函数位于基类，凡是植物，没有特殊要求的，都默认执行这两个函数：

```
QRectF Plant::boundingRect() const
{
    return QRectF(180, 0, 64, 70);
}

void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawImage(boundingRect(), movie->currentImage());
    painter->drawRect (boundingRect());
}
```
下面来说一些关键植物（派生类）大致是怎么实现的：
#### 豌豆射手Peashooter
这些都是每种植物都有的基本成员，后面的植物不再赘述：
```cpp
成员函数：
Peashooter(QPointF point);
~Peashooter();
void advance(int phase);

成员变量：
 Pea *pea; // 生成豌豆
 int peaCounter, peaCreateTime; // 第一个有计时器的功能，第二个是豌豆生成间隔
```
再来看看是怎么实现这三个函数的：

```cpp
//构造函数
Peashooter::Peashooter(QPointF point) // 该形参是告诉豌豆射手的位置在哪
{
    HP = 300; peaCounter = 0; peaCreateTime = 42; // 各种初始化，不解释
    name = "Peashooter";
    movie = new QMovie(":/graphics/Plants/" + name + "/1.gif"); // 播动画
    movie->start();
    posX = point.x()-32; // 位置调整，因为鼠标点击种植的位置与植物的位置有偏差
    posY = point.y()-35;
    setPos(posX-180, posY); // 算好位置，放植物
}

//析构函数
Peashooter::~Peashooter()
{
    Map::PlantMap[(posX-250)/80][(posY-100)/90] = nullptr; //这里是告诉Map，我要走了，麻烦你把我这个位置设置成空指针
    if(movie) //删除动画，释放内存
        delete movie;
}
```
豌豆射手的`advance`函数是用来发射豌豆的：

```cpp
void Peashooter::advance(int phase)
{
    if(!phase)
        return;
    update();
    if(peaCounter < peaCreateTime) //没到发射时间，计时器继续工作
        ++peaCounter;
    if(peaCounter == peaCreateTime) //到时间了，该发射豌豆了
    {
        pea = new Pea(QPointF(posX+50, posY));
        scene()->addItem(pea);
        peaCounter = 0;
    }
    if(HP <= 0)
        delete this;
}
```
寒冰射手、双重射手与豌豆射手类似，请见具体代码，这里不再赘述。注意，寒冰射手的豌豆具有减慢效果，它的豌豆可以调整僵尸的速度因子：

```cpp
zombie->speedFactor = 20; //僵尸速度将降到原来的20%
```
#### 樱桃炸弹CherryBomb
樱桃炸弹是少有的几个需要碰撞检测的植物，它的碰撞检测`collidesWithItem()` 需要重写。除此之外，`advance`函数也与其他植物不同：

```cpp
void Cherrybomb::advance(int phase)
{
    if(!phase)
        return;
    update();
    if(!atkStatus && counter == prepareTime) //如果已经完成准备工作
    {
        delete movie;
        movie = new QMovie(":/graphics/Plants/" + name + "/Boom.gif");
        movie->start();
        atkStatus = 1;
    }
    if(atkStatus) //如果处于攻击状态
    {
        QList<QGraphicsItem *> items = collidingItems(); //开始监测周围僵尸
        foreach(QGraphicsItem *item, items)
        {
            Zombie *zombie = qgraphicsitem_cast<Zombie *>(item);
            zombie->HP -= ATK;
            if(zombie->HP <= 0)
                zombie->setStatus = -1; //僵尸直接死亡
        }
        if(movie->currentFrameNumber() == movie->frameCount() - 1)
           delete this; //如果爆炸动画播完，删除植物
    }
    else //如果还在准备状态
        counter++;
    if(HP <= 0)
       delete this;
}
```
注意，土豆地雷与樱桃炸弹非常类似，只不过爆炸范围没有后者强，因此两者代码是基本相同的，这里不再赘述。

### 4. 僵尸Zombie
僵尸的动画比植物要复杂，随着HP的不同，僵尸的动画也会随之变化，因此僵尸的实现有些复杂。下面是僵尸的成员变量：

```cpp
enum { Type = UserType + 2}; //僵尸类型是2
int HP, crHP, ATK, setStatus; 
// 总血量； 临界血量； 攻击力； 设置状态，这个待会会详细解释
int speedFactor; // 速度调整因子
int nowStatus // 僵尸现在的状态，初始值为1
int snowCounter; // 缓慢效果计时器
qreal speed; // 僵尸行进速度
bool isHead; // 用来记录僵尸有没有头
int posX, posY; // 僵尸初始位置
QString name; // 僵尸名字
QMovie *movie, *head; // 播放动画，前者播放身体动画，后者是头掉落的动画
```
下面是僵尸的成员函数：

```cpp
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
  void advance(int phase);
  bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
  int type() const;
  void bodyMovie(QString pic); //这两个函数都是用来播放动画
  void headMovie(QString pic);
```
这里着重介绍一下`advance`函数，在`advance`函数中，分为三个部分：

 - 检查状态
 - 设置状态
 - 确定状态
 
 为了更好地控制僵尸的动作状态，我们引入了一个状态系统，用状态码来标识每种僵尸的每个动作，见下表：
|状态码| 普通僵尸 |足球/路障/铁桶僵尸|报纸僵尸|
|--|--|--|--|
| -1 | 爆炸死亡 |爆炸死亡|爆炸死亡|
|0|正常死亡|正常死亡|正常死亡
|1|有头走路|有装饰物走路|有报纸走路
|2|有头攻击|有装饰物攻击|有报纸攻击
|3|无头走路|无装饰物走路|无报纸走路
|4|无头攻击|无装饰物攻击|无报纸攻击
|5|无| 无头走路|无头走路
|6|无|无头攻击|无头攻击

如上表所见，每个状态码都有一个相对应的动作。那么我们是怎么确定僵尸要做哪个动作？见下面的足球僵尸例子，你可以对应上表参照：

```cpp
 QList <QGraphicsItem *> items = collidingItems();
    if(setStatus != -1)//如果爆炸死亡的，就直接-1，不管HP了
    {
     if(HP >= ornHP){           // HP=270-350 有头盔
        setStatus = 1;
        if(!items.isEmpty()){   // 如果碰到植物
            setStatus = 2;
            plant = qgraphicsitem_cast<Plant *> (items[qrand() % items.size()]);
        }
     }
     else if(HP >= crHP){  //HP=70-270 无头盔
        setStatus = 3;
        if(!items.isEmpty()){   // 如果碰到植物
            setStatus = 4;
            plant = qgraphicsitem_cast<Plant *> (items[qrand() % items.size()]);
        }
     }
     else if(HP > 0){        // 0-70 到达临界值不再有攻击力，HP匀速减少
        HP--;
        setStatus = 5;
        if(!items.isEmpty()){
            setStatus = 6;   // 如果碰到植物
            plant = qgraphicsitem_cast<Plant *> (items[qrand() % items.size()]);
        }
    }
    else                    // <0 死亡
        setStatus = 0;
    }
```
这是僵尸的`advance`函数的第一个部分：确定（检查）状态。僵尸初始化时，都默认是状态码1。每次调用该函数时，都要由这部分代码检查状态。

下面是第二个部分，这部分是用于设置状态，设置完成后，播放相对应的动画：

```cpp
switch(setStatus)
    {
    case -1:
        speedFactor = 100;
        if(setStatus != nowStatus)
           bodyMovie(":/graphics/Zombies/" + name + "/BoomDie.gif");
        break;
    case 0:
        speedFactor = 100;
       if(setStatus != nowStatus)
       {
          bodyMovie(":/graphics/Zombies/" + name + "/Die.gif");
          if(isHead) //如果死的时候有头，麻烦把掉落头部的动画也播放一下
              headMovie(":/graphics/Zombies/Zombie/ZombieHead.gif");
       }
       break;
    case 1:
       if(setStatus != nowStatus)
         bodyMovie(":/graphics/Zombies/" + name + "/" + name + ".gif");
       setX(x() - speed * speedFactor / 100);
       break;
    case 2:
       if(setStatus != nowStatus)
            bodyMovie(":/graphics/Zombies/" + name + "/" + name + "Attack.gif");
       plant->HP -= ATK * speedFactor / 100;
       break;
    case 3:
       if(setStatus != nowStatus)
            bodyMovie(":/graphics/Zombies/" + name + "/" + name + "OrnLost.gif");
       setX(x() - speed * speedFactor / 100);
       break;
    case 4:
        if(setStatus != nowStatus)
            bodyMovie(":/graphics/Zombies/" + name + "/" + name + "OrnLostAttack.gif");
        plant->HP -= ATK * speedFactor / 100;
       break;
    case 5:
       if(setStatus != nowStatus)
       {
          bodyMovie(":/graphics/Zombies/" + name + "/LostHead.gif");
          if(isHead)
              headMovie(":/graphics/Zombies/Zombie/ZombieHead.gif");
       }
       setX(x() - speed * speedFactor / 100);
       break;
    case 6:
       if(setStatus != nowStatus)
       {
            bodyMovie(":/graphics/Zombies/" + name + "/LostHeadAttack.gif");
            if(isHead)
                headMovie(":/graphics/Zombies/Zombie/ZombieHead.gif");
       }
        break;
    default:
        break;
    }
```
设置完状态后，进入第三个操作：`nowStatus = setStatus;`，这是告诉僵尸，你的这个状态已经被确定了。如果下一次检查还是这个状态，那么将不会设置状态，除非下一次检查发现状态变了。这就是`if(setStatus != nowStatus)`的作用。

僵尸的实现基本上都是一致的，都是重复造轮子，就不多说了。

下面着重讲述我几个遇到的问题。

## 三、问题与解决
其实很多问题都可以通过阅读Qt官方文档就能解决，整个编写过程还算顺利。只不过，由于一开始没有用对框架，导致前期浪费了时间，所以完工的比较仓促。
### 1. 关于游戏暂停
之前没有使用`QGraphicsScene`框架写代码的时候就被这个问题困住，不过后来更换了框架之后，想到可以将所有动画绑定到定时器上，我只要来个`timer->stop()`就可以马上停止了。
### 2. 关于鼠标光标
点击卡牌，鼠标光标变成植物形状。之后左击地图，表示放置植物，光标恢复；右击地图，表示取消放置植物，光标恢复。因为整个窗口都需要光标显示为植物形状，因此只好使用` QApplication::setOverrideCursor(cursor);`，后面用了` QApplication::restoreOverrideCursor();`光标恢复以后，所有子部件的光标都变成同一个光标了。

上网查了一下，才知道`QApplication::restoreOverrideCursor ()`是撤销最近一次的`setOverrideCursor()`。如果`setOverrideCursor()`已经被调用两次，调用`restoreOverrideCursor()`会激活第一个光标设置。第二次调用这个函数会恢复初始窗口部件的光标。可以这么理解，`QApplication::setOverrideCursor(cursor);`是光标入栈，而`restoreOverrideCursor()`是光标出栈。查了查我写的程序，发现确实有两个`setOverrideCursor()`，而只有一个`restoreOverrideCursor()`，这就是问题所在了。

### 3. 关于坐标系统
许多物体的位置和碰撞检测都需要慢慢调试，因为窗口、view、scene和每个item都有自己的坐标系统，必须对这些要熟悉。最好加上`qDebug`慢慢调试。
### 4. 关于内存泄露
这个我有些体会。每个对象消亡后都要`delete`指针，释放内存。在经历许多次程序崩溃后终于明白，每一次`delete`之后指针并不会指向空指针，而是成为了野指针。最安全的做法是`delete`以后将其指向`nullptr`。空指针也是可以被`delete`的。

### 5. 关于游戏音乐
我将素材的音乐转换成`WAV`格式，但是`QSound`依然无法播放文件，这是因为比特率太大的缘故。想要播放`mp3`格式的文件应该用`QMediaPlayer`。由于时间比较紧，我没有实现这部分功能，但是经过测试，此方法可行。

### 6. 两个item的叠加顺序不正确
比如，按照逻辑，第二行的僵尸应该是遮住第一行的僵尸。所以，我又去查了官方文档。。。原来有这两个函数：`setZValue`和`stackBefore`。默认的Z值是0，具有同样的Z值的item会按照插入的顺序来入栈。也就是说，`GraphicsView`会优先根据item的Z值决定item的层次，Z大的在上面，Z小的在下面，只有当Z值相同的情况下才会去理会`stackBefore`函数。这个函数在Z相同的情况下，允许你决定哪个在上哪个在下。

### 7.关于分辨率
这个问题是截止日期快到的时候才发现的，没来得及解决，加上`QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);`也没用。只好设置分辨率1440X900下再打开程序吧。

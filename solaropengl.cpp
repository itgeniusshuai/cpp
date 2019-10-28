#include "solaropengl.h"
#include <math.h>
#include <QTimer>
#include <QPixmap>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <QDebug>


SolarOpenGL::SolarOpenGL(QWidget *parent) : QGLWidget(parent)
{

    Planet* sun= new Planet(0,24*365,0.0f,":/pic/vein/sun.jpg", 18, "太阳", PlanetType::FIXED, 696300);
    Planet* mercury = new Planet(1,24*88,0.0f,":/pic/vein/mercury.jpg", 58*24, "水星", PlanetType::PLANET, 2440/2);
    Planet* venus = new Planet(2,24*224,177.0f,":/pic/vein/venus.jpg", 243*24, "金星", PlanetType::PLANET, 12103/2);
    Planet* earth = new Planet(3,24*365,23.0f,":/pic/vein/earth.bmp", 24, "地球", PlanetType::PLANET, 6400);
    Planet* mars = new Planet(4,24*687,25.0f,":/pic/vein/mars.jpg", 24, "火星", PlanetType::PLANET, 6794/2);
    Planet* jupiter = new Planet(5,24*365*12,1.0f,":/pic/vein/jupiter.jpg",10, "木星", PlanetType::PLANET, 142984/2);
    Planet* saturn = new Planet(6,24*10832,27.0f,":/pic/vein/saturn.jpg", 11, "土星", PlanetType::PLANET, 120536/2);
    Planet* uranus = new Planet(7,24*365*84,92.0f,":/pic/vein/uranus.jpg", 17, "天王星", PlanetType::PLANET, 51118/2);
    Planet* neptune = new Planet(8,60327*24,28.32f,":/pic/vein/neptune.jpg", 16, "海王星", PlanetType::PLANET, 49532/2);
    Planet* moon = new Planet(1,24*30,10.0f,":/pic/vein/moon.jpeg", 27, "月球", PlanetType::MOON, 3476/2);

    QList<Planet*> sunSubPlanets;
    QList<Planet*> earthSubPlanets;

    sunSubPlanets.push_back(mercury);
    sunSubPlanets.push_back(venus);
    sunSubPlanets.push_back(earth);
    sunSubPlanets.push_back(mars);
    sunSubPlanets.push_back(jupiter);
    sunSubPlanets.push_back(saturn);
    sunSubPlanets.push_back(uranus);
    sunSubPlanets.push_back(neptune);
    sun->setSubPlanets(sunSubPlanets);

    earthSubPlanets.push_back(moon);
    earth->setSubPlanets(earthSubPlanets);

    this->sun = sun;

    //创建一个定时器
   QTimer *timer = new QTimer(this);
   timer->setInterval(10);
   //将定时器的计时信号与updateGL()绑定
   connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
   timer->start();

}

void SolarOpenGL::initializeGL()                         //此处开始对OpenGL进行所以设置
{
    glClearColor(0.0, 0.0, 0.0, 0.0);                   //黑色背景
    glShadeModel(GL_SMOOTH);                            //启用阴影平滑
    glEnable(GL_TEXTURE_2D);  // 启用纹理

    glClearDepth(1.0);                                  //设置深度缓存
    glEnable(GL_DEPTH_TEST);                            //启用深度测试
    glDepthFunc(GL_LEQUAL);                             //所作深度测试的类型
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //告诉系统对透视进行修正

    GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};  //环境光参数
    GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};  //漫散光参数
    GLfloat LightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f}; //光源位置
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);     //设置环境光
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);     //设置漫射光
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   //设置光源位置
    glEnable(GL_LIGHT1);                                //启动一号光源

}

void SolarOpenGL::resizeGL(int w, int h)                 //重置OpenGL窗口的大小
{
    glViewport(0, 0, (GLint)w, (GLint)h);               //重置当前的视口
    glMatrixMode(GL_PROJECTION);                        //选择投影矩阵
    glLoadIdentity();                                   //重置投影矩阵
    //设置视口的大小

    gluPerspective(60.0, static_cast<GLfloat>(w)/static_cast<GLfloat>(h), 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);                         //选择模型观察矩阵
    glLoadIdentity();                                   //重置模型观察矩阵
}

void SolarOpenGL::paintGL()                              //从这里开始进行所以的绘制
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除屏幕和深度缓存
    glLoadIdentity();                                   //重置当前的模型观察矩阵

    // 让视角更远
    glTranslatef(0,0,-10);
    // 画太阳，递归画出九大行星
    this->drawPlanet(sun);

}

void SolarOpenGL::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    //F1为全屏和普通屏的切换键
    case Qt::Key_F1:
        showNormal();
        updateGL();
        break;
    //ESC为退出键
    case Qt::Key_Escape:
        close();
    }
}

void SolarOpenGL::drawPlanet(Planet * planet){
//    qDebug() << planet->getPlantName() << "r:" << planet->getRealRevolutionR();
    // 确定该球的位置
    if(planet->getPlanetType() != PlanetType::FIXED){
        // 延y轴转动(公转)
        float revolutionAngle = planet->calRevolutionAngle();
        planet->setRevolutionAngle(revolutionAngle + planet->getRevolutionAngle());
        glRotatef(planet->getRevolutionAngle(),0,0,1);
    }
//    // 公转半径偏移
    glTranslatef(planet->getRealRevolutionR(),0,0);
    if(planet->getPlanetType() != PlanetType::FIXED){
        // 延z轴转动(自转)
        float ownRevolutionAngle = planet->calOwnRevolutionAngle();
        planet->setOwnRevolutionAngle(ownRevolutionAngle + planet->getOwnRevolutionAngle());
        glRotatef(-90,1,0,0);
        glRotatef(-planet->getObliquity(),0,1,0);
        glRotatef(planet->getOwnRevolutionAngle(),0,0,1);

    }
    // 画球
    drawSphere(planet);

    QList<Planet*> subPlanets = planet->getSubPlanets();
    if(subPlanets.size() != 0){
        for (int i = 0; i < subPlanets.size(); i++) {
            // 记录父亲位置
            glPushMatrix();
            this->drawPlanet(subPlanets[i]);
            glPopMatrix();
       }
    }

}

void SolarOpenGL::drawSphere(Planet *planet){
    GLuint m_Texture = bindTexture(*planet->getImage());
    glEnable(GL_TEXTURE_2D);

    GLUquadricObj *quadObj = gluNewQuadric();//创建一个二次曲面物体
    gluQuadricTexture(quadObj,GL_TRUE);        //启用该二次曲面的纹理
    glBindTexture(GL_TEXTURE_2D, m_Texture);//绑定纹理
    //绘制一个球体
    double r = 0.3;
    if(PlanetType::MOON == planet->getPlanetType()){
        r = 0.1;
    }
    if(PlanetType::FIXED ==  planet->getPlanetType()){
        r = 0.5f;
    }
    gluSphere(quadObj,r,20,20);                    //绘制一个球体
    gluDeleteQuadric(quadObj);                   //删除二次曲面对象
}

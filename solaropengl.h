#ifndef MYOPENGL_H
#define MYOPENGL_H

#include <QWidget>
#include <QGLWidget>
#include <QKeyEvent>
#include "planet.h"


class SolarOpenGL : public QGLWidget
{
    Q_OBJECT
public:
    explicit SolarOpenGL(QWidget *parent = nullptr);
    //对3个纯虚函数的重定义
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent *event);           //处理键盘按下事件

    void drawPlanet(Planet* planet);
    void drawSphere(Planet* planet);

signals:

public slots:

private:
    float m_rti;
    float x;
    float y;
    float z;
    Planet* sun;

};

#endif // MYOPENGL_H

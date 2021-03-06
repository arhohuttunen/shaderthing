#ifndef SHADER_THING_OPENGL_WIDGET_H
#define SHADER_THING_OPENGL_WIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QTime>
#include <QVector2D>

class QOpenGLShaderProgram;

class ShaderThingOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    ShaderThingOpenGLWidget(QWidget *parent = 0);
    ~ShaderThingOpenGLWidget();

    QString compileShader(QString shader);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private slots:
    void render();

private:
    void startTimer();

    QTimer *timer;
    QTime elapsedTime;
    QOpenGLShaderProgram *shaderProgram;
    QVector2D resolution;
};

#endif // SHADER_THING_OPENGL_WIDGET_H

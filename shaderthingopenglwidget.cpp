#include <QOpenGLShader>
#include "shaderthingopenglwidget.h"

ShaderThingOpenGLWidget::ShaderThingOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), shaderProgram(NULL)
{
}

ShaderThingOpenGLWidget::~ShaderThingOpenGLWidget()
{
}

QString ShaderThingOpenGLWidget::compileShader(QString shader)
{
    QOpenGLShader *vertexShader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vertexShader->compileSourceCode(
        "void main()"
        "{"
        "gl_Position = gl_Vertex * gl_ModelViewProjectionMatrix;"
        "}"
    );

    QOpenGLShader *fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    if (!fragmentShader->compileSourceCode(shader))
        return fragmentShader->log();

    shaderProgram = new QOpenGLShaderProgram(this);
    shaderProgram->addShader(vertexShader);
    shaderProgram->addShader(fragmentShader);
    if (!shaderProgram->link())
        return shaderProgram->log();

    startTimer();

    return QString();
}

void ShaderThingOpenGLWidget::initializeGL()
{
    glClearColor(0.1, 0.2, 0.3, 1.0);

    glOrtho(-1.0, 1.0, -1.0, 1.0, 0.1, 10.0);
    glTranslatef(0.0, 0.0, -1.0);
}

void ShaderThingOpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!shaderProgram || !shaderProgram->isLinked())
        return;

    shaderProgram->bind();
    shaderProgram->setUniformValue("time", elapsedTime.elapsed() / 1000.0f);
    shaderProgram->setUniformValue("resolution", resolution);

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(-1.0, -1.0, 0.0);
    glVertex3f(1.0, -1.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(-1.0, 1.0, 0.0);
    glEnd();
}

void ShaderThingOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    resolution = QVector2D((float) w, (float) h);
}

void ShaderThingOpenGLWidget::startTimer()
{
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(render()));
    timer->start(10);
    elapsedTime.start();
}

void ShaderThingOpenGLWidget::render()
{
    update();
}

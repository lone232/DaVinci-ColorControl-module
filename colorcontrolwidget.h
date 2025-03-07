#ifndef COLORCONTROLWIDGET_H
#define COLORCONTROLWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVector2D>

struct ColorOffset
{
    double red;
    double green;
    double blue;
    ColorOffset(double red, double green, double blue)
        :red(red), green(green), blue(blue){}
};


class ColorControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorControlWidget(QWidget *parent = nullptr);
    ColorOffset getOffset(){
        return offset;
    }
protected:
    void paintEvent(QPaintEvent* ) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    // 色环中心
    QPointF center;
    // 色环半径
    qreal radius = 50;
    // 中间的白点
    QLabel *dragPoint;
    // 白点是否被拖动
    bool isDragging = false;
    // 偏移数据
    ColorOffset offset = ColorOffset(0.0,0.0,0.0);
    //
    QPointF pressedPos;
    //
    QPoint dragPointPos;

    virtual void drawColorWheel(QPixmap*);
    virtual void drawColorWheel(QPainter*);
    QPixmap applyBlurEffect(const QPixmap &source);
    bool isDragPointInColorWheel(QMouseEvent *event);
    ColorOffset resolveColorOffset(QPointF);
    double projectLenth(const QVector2D &a, const QVector2D &b);
signals:
    void dragPointChange();
};

#endif // COLORCONTROLWIDGET_H

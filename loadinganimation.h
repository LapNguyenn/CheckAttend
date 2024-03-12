#ifndef LOADINGANIMATION_H
#define LOADINGANIMATION_H

#include <QObject>
#include <QLabel>
#include <QMovie>

class LoadingAnimation : public QObject
{
    Q_OBJECT
public:
    LoadingAnimation(QLabel *label, QObject *parent = nullptr);
    ~LoadingAnimation();
public slots:
    void startLoading();
    void stopLoading();

private:
    QLabel *lbl;
    QMovie *movie;
};

#endif // LOADINGANIMATION_H

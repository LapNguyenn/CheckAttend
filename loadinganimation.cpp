#include "loadinganimation.h"


LoadingAnimation::LoadingAnimation(QLabel *label, QObject *parent)
    :QObject(parent), lbl(label)
{
    movie = new QMovie(":/assets/gifs/loading.gif");
    movie->setScaledSize(lbl->size());
    lbl->setMovie(movie);
}

LoadingAnimation::~LoadingAnimation()
{
    delete movie;
}

void LoadingAnimation::startLoading()
{
    lbl->show();
    movie->start();
}

void LoadingAnimation::stopLoading()
{
    movie->stop();
    lbl->hide();
}

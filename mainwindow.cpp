#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "afuncs.h"
#include <cmath>
#include "a_macro.cpp"

#define N0_LEN    3
#define N1_LEN    3
#define N2_LEN    3


#define LAYER_QTY 3

double arrN0[N0_LEN];
double arrN1[N1_LEN];
double arrN2[N2_LEN];

double arrW1[N1_LEN][N0_LEN];
double arrW2[N2_LEN][N1_LEN];

 double arrG[N2_LEN];

AFuncs *mf;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mf = new AFuncs;

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    //timer->start(100);

    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,218,108);
    ui->img1->setScene(scene);

    G_sigmoidTilt = 15;
    initWeights();
}

MainWindow::~MainWindow()
{
    delete ui;
}
//------------------------------------------------------------------------------------------------------------------


double MainWindow::getSingleWeight(double  *neurs, double *wts, int wtQty)
{
    int i;
    double res = 0;
    double tmp;
    for (i = 0; i < wtQty; i++) {
       tmp = neurs[i]*wts[i];
       res += tmp;
    }
    res = mf->getSigmoid(res, G_sigmoidTilt);
    return res;
}

//------------------------------------------------------------------------------------------------------------------

double MainWindow::getWeightForLayer(int layerNum, double * layerNeurs)
{
    int i;
    double err;

    for (i = 0; i < N1_LEN; i++) {
        arrN1[i] = getSingleWeight(arrN0, arrW1[i], N0_LEN);
    }

    for (i = 0; i < N2_LEN; i++) {
        arrN2[i] = getSingleWeight(arrN1, arrW1[i], N1_LEN);
    }

    for (i = 0; i < N2_LEN; i++) {
        err = pow((arrN2[i]-arrG[i]),2);

    }


//        getWeights(w1[k], n1, n2[k], goal[k], 3);

//        errStr  =  QString::number(err);
//        resStr  = QString::number(n2[k]);
//        ui->lb1->append("err->"+errStr+"; res->"+resStr);



}
//------------------------------------------------------------------------------------------------------------------


void MainWindow::on_edN1_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    double val;
    QString str = ui->edN1->text();
    if (!checkStrDouble(str, &val, ui->edN1)) return;
}
//------------------------------------------------------------------------------------------------------------------

bool MainWindow::checkStrDouble(QString str, double *value, QLineEdit *ed, bool chngColor)
{
     bool valid;
     double val  = str.toDouble(&valid);
     if (valid) {
         *value = val;
         ed->setStyleSheet("background-color : white;");
         return true;
     }else {
        if(chngColor)  ed->setStyleSheet("background-color : red;");
         return false;
     }

}
//------------------------------------------------------------------------------------------------------------------

void MainWindow::on_btSigmoid_clicked()
{

    int x,y,i;
    double z, step;


    if (!checkStrDouble(ui->edSigStep->text() , &step, ui->edSigStep, false)) step = 15;

    z=0;
    scene->clear();

    for (i = 0; i < 100; i++) {
       y = mf->getSigmoid(z, step)*100;
       x=i*2+10;
       z+=0.01;
       y=105-y;

        scene->addLine(x,y,x,y);
    }


}
//------------------------------------------------------------------------------------------------------------------

void MainWindow::timerSlot()
{
    static int x = 0;
    QString str = QString::number(x);
    ui->lbl1->setText(str);

    static float a = 0;
    a+=0.1;

    int y = cos(a)*50+100;

    scene->addLine(x,y,x,y);


    x++;
    if (x>390) {
        timer->stop();
    }
}
//------------------------------------------------------------------------------------------------------------------

void MainWindow::initWeights()
{
    double x;
    int i,k, cnt=1;

    for (i = 0; i < N0_LEN; i++) {
        for (k = 0; k < N1_LEN; k++) {
            srand(cnt++);
            x = (double)(rand()%100)/100;
            arrW1[i][k] = x;
        }
    }

    for (i = 0; i < N1_LEN; i++) {
        for (k = 0; k < N2_LEN; k++) {
            srand(cnt++);
            x = (double)(rand()%100)/100;
            arrW2[i][k] = x;
        }
    }


}
//----------------------------------------------------------------------------------------------------------------------------

double MainWindow::sumWeights(double*inp, double*wt, int wtQt)
{
    int i;
    double res = 0;
    double tmp;
    for (i = 0; i < wtQt; i++) {
       tmp = inp[i]*wt[i];

       res += tmp;
    }
  //  res = mF->getSigmoid(res, 15);
    return res;
}
//----------------------------------------------------------------------------------------------------------------------------

void MainWindow::getLastLayerWeights(double*wt, double*inp, double res, double goal, int qt)
{
   int i;
   double dir;
   double alfa = ui->edAlfa->text().toDouble();

   for (i = 0; i < qt; i++) {
      dir = (res-goal)*inp[i];
      wt[i] -= dir*alfa;
   }
}
//----------------------------------------------------------------------------------------------------------------------------

void MainWindow::loadInputsGoalsData(){
    arrN0[0] = ui->edN1->text().toDouble();
    arrN0[1] = ui->edN2->text().toDouble();
    arrN0[2] = ui->edN3->text().toDouble();

    arrG[0] = ui->edGoal1->text().toDouble();
    arrG[1] = ui->edGoal2->text().toDouble();
    arrG[2] = ui->edGoal3->text().toDouble();
}
//----------------------------------------------------------------------------------------------------------------------------


void MainWindow::on_pushButton_6_clicked()
{
    int i,k;
    QString errStr, resStr;

    double  err;

    ui->lb1->clear();
    arrN0[0] = ui->edN1->text().toDouble();
    arrN0[1] = ui->edN2->text().toDouble();
    arrN0[2] = ui->edN3->text().toDouble();
    arrG[0] = ui->edGoal1->text().toDouble();
    arrG[1] = ui->edGoal2->text().toDouble();
    arrG[2] = ui->edGoal3->text().toDouble();

    for (  i = 0; i < 40; i++){
        mf->matrixMul(arrN0, 3, M_ARR(3,3,arrW1),   arrN1);
        mf->getSigmoid(arrN1, N1_LEN, G_sigmoidTilt);
        for(k=0; k<3; k++){
             err = pow((arrN1[k]-arrG[k]),2);
             getLastLayerWeights(arrW1[k], arrN0, arrN1[k], arrG[k], 3);
             errStr  =  QString::number(err);
             resStr  = QString::number(arrN1[k]);
             ui->lb1->append("err->"+errStr+"; res->"+resStr);
        }
    }
    ui->edOut1->setText(QString::number(arrN1[0]));
    ui->edOut2->setText(QString::number(arrN1[1]));
    ui->edOut3->setText(QString::number(arrN1[2]));
}
//----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_btLern_clicked()
{
    int i,k;
    double err;
    loadInputsGoalsData();
    ui->lb1->clear();
    QString errStr, resStr;
    for (  i = 0; i < 40; i++) {
       for (  k = 0; k < 3; k++){
            arrN1[k] = sumWeights(arrN0,arrW1[k],3);
       }

       for (  k = 0; k < 3; k++) {

            err = pow((arrN1[k]-arrG[k]),2);
            getLastLayerWeights(arrW1[k], arrN0, arrN1[k], arrG[k], 3);
            errStr  =  QString::number(err);
            resStr  = QString::number(arrN1[k]);
            ui->lb1->append("err->"+errStr+"; res->"+resStr);


       }
    }

    ui->edOut1->setText(QString::number(arrN1[0]));
    ui->edOut2->setText(QString::number(arrN1[1]));
    ui->edOut3->setText(QString::number(arrN1[2]));

}

void MainWindow::on_pushButton_clicked()
{
    initWeights();
}

void MainWindow::on_pushButton_2_clicked()
{
    double arrM[50];
    loadInputsGoalsData();
    ui->lb1->clear();

    mf->matrixMul(arrN0, 3, M_ARR(3,3,arrW1),   arrN1);
    mf->getSigmoid(arrN1, N1_LEN, G_sigmoidTilt);

//    for (int var = 0; var < 3; ++var) {
//        arrN1[var] =  mf->getSigmoid(arrN1[var], G_sigmoidTilt);
//    }




   ui->edOut1->setText(QString::number(arrN1[0]));
   ui->edOut2->setText(QString::number(arrN1[1]));
   ui->edOut3->setText(QString::number(arrN1[2]));

}

void MainWindow::on_edSigTilt_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    double val;
    if(checkStrDouble(ui->edSigStep->text(), &val, ui->edSigStep)){
        G_sigmoidTilt = val;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    int i;
    int a[4][2] = {{1 ,  2,},
                        {3,  4},
                        {5,  7},
                        {7,  8}};
    int a1[2][3] = {{2,4,6},
                         {7,8,9}};
    int res[4][3];
    mf->matrixMul(M_ARR(4,2,a), M_ARR(2,3,a1), M_ARR(4,3,res));

    i=0;

}

void MainWindow::on_pushButton_4_clicked()
{
    int i;
    int a[2][2] = {{2 ,  1,},
                        {5,  4}};
    int a1[2][2] = {{3,  4},
                         {7,  8}};
    int res[2][2];
    mf->matrixMul(M_ARR(2,2,a), M_ARR(2,2,a1), M_ARR(2,2,res));

    i=0;
}

void MainWindow::on_pushButton_5_clicked()
{
    int i;
    int a[1][4]   = { 2, 1, 5, 4 };
    int a1[1][4] = { 3, 4, 7, 8 };

    int res[1][1];
    mf->matrixMul(M_ARR(1,4,a), M_ARR(4,1,a1), M_ARR(1,1,res));

    i=0;
}


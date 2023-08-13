#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTimer>
#include <QGraphicsScene>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:

    void on_edN1_textChanged(const QString &arg1);

    void on_btSigmoid_clicked();
    void timerSlot();
    void on_pushButton_clicked();

    void on_btLern_clicked();

    void on_pushButton_2_clicked();

    void on_edSigTilt_textChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:



    double n1[3],
               n2[3],
               n3[3];

    double w1[3][3],
               w2[3][3],
               w3[3][3];

    double G_sigmoidTilt;



    Ui::MainWindow *ui;
    QTimer *timer;
    QGraphicsScene *scene;

    bool checkStrDouble(QString str, double *value, QLineEdit *ed,  bool chngColor = true);

    double getCorrectWeight(double in, double goal, double *wt, double alfa);
    void initWeights();
    double sumWeights(double *inp, double *wt, int wtQt);
    void getWeights(double *wt, double *inp, double res, double goal, int qt);
    void loadInputsGoalsData();
    double getWeightForLayer(int layerNum, double *layerNeurs);

    double getSingleWeight(double *wts, double *neurs, int wtQty);

    void tmpFunc(int l1, int r1, int a1[], int l2, int r2, int a2[], int lRes, int rRes, int result[]);
};

#endif // MAINWINDOW_H

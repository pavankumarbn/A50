#include "autotest.h"
#include "ui_autotest.h"

AutoTest::AutoTest(QWidget *parent)
    : QWidget(parent), ui(new Ui::AutoTest), test(0) {
  ui->setupUi(this);
}

AutoTest::~AutoTest() { delete ui; }

DJI::onboardSDK::CoreAPI *AutoTest::getAPI() const { return api; }

void AutoTest::setAPI(DJI::onboardSDK::CoreAPI *value) { api = value; }

CoreTest::CoreTest(DJI::onboardSDK::CoreAPI *API) : Test(API) {
  cmdline::parser *tmp = 0;
  tmp                  = new cmdline::parser();
  tmp->set_program_name("test");
  tmp->add("help", 0, "help message");
  parserMap.insert("test", tmp);
}

void CoreTest::enterence(std::string s) {
  QString str     = QString::fromStdString(s);
  QStringList lst = str.split(" ");
  qDebug() << lst;
  str.remove(0, lst[0].length());
  str.remove(0, 1);
  qDebug() << str;
  QMap<QString, cmdline::parser *>::const_iterator i = parserMap.find(lst[0]);

  while (i != parserMap.end() && i.key() == lst[0]) {
    qDebug() << i.value() << "Paser" << endl;
    if ((*i)->parse(str.toStdString()))
      qDebug() << "ok";
    else
      qDebug() << "fail";
    ++i;
  }
}

void AutoTest::on_btn_send_clicked() {
  QString str = ui->le_inject->text();
  test->injectFeedback(str.length(), str.toLocal8Bit().data());
}

#include "newexodialog.h"
#include "preferences.h"
#include "ui_newexodialog.h"
#include <QFileInfo>
#include <QTextStream>

NewExoDialog::NewExoDialog(QWidget *parent,QString fileName,QStringList metas) :
    QDialog(parent),
    ui(new Ui::NewExoDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(create()));

    metas_m = metas;
    fileName_m = fileName;
    setWindowTitle(QFileInfo(fileName).fileName());

    // Create layout objets

    for (int i=0;i<metas.size();i++) {
        QLabel * label = new QLabel(metas.at(i),this);
        QLineEdit * line = new QLineEdit(this);
        QHBoxLayout * hlayout = new QHBoxLayout();
        labelList.append(label);
        lineList.append(line);
        labelList.at(i)->setBuddy(lineList.at(i));
        hlayout->addWidget(labelList.at(i));
        hlayout->addWidget(lineList.at(i));
        ui->verticalLayout->addLayout(hlayout);
    }
}

void NewExoDialog::create() {

    // Texte de l'entête
    QString fileText = "";
    for (int i=0;i<metas_m.size();i++) {
        fileText += "%@ "+metas_m.at(i)+": "+lineList.at(i)->text() + "\n";
    }

    // On le crée (en ouvrant un fichier qui n'existe pas cela le crée)
    QFile file(fileName_m);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;
    QTextStream textStream(&file);
    textStream.flush();
    bool useIso = Preferences::p_getUseIso();
    if (useIso) textStream.setCodec("ISO 8859-15");
    textStream << fileText;
    file.close();
}

NewExoDialog::~NewExoDialog()
{
    delete ui;
}

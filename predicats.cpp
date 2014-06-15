#include "predicats.h"
#include "utmanager.h"
#include "utprofilerexception.h"
#include "ui_predicatXUVParmis.h"
#include "ui_predicatMinimumCreditInCategory.h"

#include <QLineEdit>
#include <QSpinBox>
#include <QInputDialog>
#include <QtDebug>

Predicat* PredicatFactory(int type)
{
    switch (type) {
    case PREDICAT_UV_OBLIGATOIRE:
        return new PredicatUVObligatoire;
        break;
    case PREDICAT_X_UV_PARMIS:
        return new PredicatXUVParmis;
        break;
    case PREDICAT_MINIMUM_CREDIT_IN_CATEGORY:
        return new PredicatMinimumCreditInCategory;
        break;
    case PREDICAT_MINIMUM_CREDIT:
        return new PredicatMinimumCredit;
        break;
    default:
        return 0;
        break;
    }
}

int PredicatDescriptionToInt(const QString &desc)
{
    if(desc == "UV obligatoire")
        return PREDICAT_UV_OBLIGATOIRE;
    else if(desc == "Obtenir X UV parmis")
        return PREDICAT_X_UV_PARMIS;
    else if(desc == "Obtenir un minimum de credit de type")
        return PREDICAT_MINIMUM_CREDIT_IN_CATEGORY;
    else if(desc == "Obtenir un minimum de credit")
        return PREDICAT_MINIMUM_CREDIT;
    else
        UTPROFILER_EXCEPTION("Type de rpédicat inconnu");
}

PredicatUVObligatoire::PredicatUVObligatoire() : Predicat(), uv() {}
bool PredicatUVObligatoire::predicatSatifait(QVector<const UV*> uvValidee)
{
    //Merci auto :-)
    for(auto it = uvValidee.begin() ; it != uvValidee.end() ; it++)
    {
        if((*it)->getCode() == uv)
            return true;
    }

    return false;
}
bool PredicatUVObligatoire::chargerParametres(QStringList &list)
{
    uv = list.first();
    return true;
}
void PredicatUVObligatoire::sauverParametre(QDomElement &elem)
{
    elem.setAttribute("type", PREDICAT_UV_OBLIGATOIRE);
    elem.setAttribute("param", uv);
}

const QString PredicatUVObligatoire::recommanderUv() //Pour valider cette condition, il faut impérativement obtenir "uv", il est donc tout naturel de la recommander
{
    return uv;
}
bool PredicatUVObligatoire::peutAmeliorerLeCursus(const QString &candidat)
{
    return candidat == uv;
}
QWidget* PredicatUVObligatoire::getEditorWidget(QWidget *parent)
{
    QHBoxLayout *lay = new QHBoxLayout(parent);
    QLineEdit *line = new QLineEdit(uv, parent);
    QWidget* container = new QWidget(parent);

    connect(line, SIGNAL(textEdited(QString)), this, SLOT(updateUv(QString)));

    lay->addWidget(new QLabel("UV obligatoire", parent));
    lay->addWidget(line);
    container->setLayout(lay);
    connect(this, SIGNAL(destroyed()), container, SLOT(deleteLater()));
    return container;
}

PredicatXUVParmis::PredicatXUVParmis() : Predicat(), minimumUV(0) {}
bool PredicatXUVParmis::predicatSatifait(QVector<const UV *> uvValidee)
{
    unsigned int nbUvValider = 0;
    for(auto it = uvValidee.begin() ; it != uvValidee.end() ; it++)
    {
        if(candidats.contains((*it)->getCode()))
            nbUvValider++;
    }

    return nbUvValider >= minimumUV;
}
bool PredicatXUVParmis::chargerParametres(QStringList &list)
{
    minimumUV = list.first().toInt();
    list.removeFirst();
    candidats = list;
    return true;
}
void PredicatXUVParmis::sauverParametre(QDomElement &elem)
{
    QString param = QString::number(minimumUV);
    for(int i = 0 ; i < candidats.size() ; i++)
    {
        param += "," + candidats[i];
    }

    elem.setAttribute("type", PREDICAT_X_UV_PARMIS);
    elem.setAttribute("param", param);
}

const QString PredicatXUVParmis::recommanderUv() //On recommande l'UV qui rapporte le plus de crédit dans la liste
{
    QString uvARecommander;

    unsigned int maxCredit = 0;

    for(auto it = candidats.begin() ; it != candidats.end() ; it++)
    {
        UV* uv = sUTManager->getUV(*it);
        if(!uv)
            UTPROFILER_EXCEPTION(QString("Ce prédicat contient une UV inconnue (%1)").arg(*it).toStdString().c_str());

        if(uv->getNombreCredit() > maxCredit)
        {
            maxCredit = uv->getNombreCredit();
            uvARecommander = uv->getCode();
        }
    }

    return uvARecommander;
}
bool PredicatXUVParmis::peutAmeliorerLeCursus(const QString &uv)
{
    return candidats.contains(uv);
}

QWidget* PredicatXUVParmis::getEditorWidget(QWidget *parent)
{
    Ui_xUVParmis_editor ui;
    QWidget *editor = new QWidget(parent);
    ui.setupUi(editor);

    ui.candidat->addItems(candidats);
    ui.count->setValue(minimumUV);
    ui.count->setMinimum(0);

    connect(ui.addUv, SIGNAL(clicked()), this, SLOT(addUv()));
    connect(ui.delUv, SIGNAL(clicked()), this, SLOT(delUv()));
    connect(ui.count, SIGNAL(valueChanged(int)), this, SLOT(updateMinimumUv(int)));
    connect(this, SIGNAL(destroyed()), editor, SLOT(deleteLater()));
    return editor;
}
void PredicatXUVParmis::addUv()
{
    QString uvCode = QInputDialog::getText(0, "Ajouter une UV", "Entrer l'UV à ajouter");
    if(uvCode.isEmpty())
        return;

    QListWidget *candidat = sender()->parent()->findChild<QListWidget*>("candidat");
    if(!candidat)
        UTPROFILER_EXCEPTION("L'editeur de prédicat est corrompu");

    if(candidats.contains(uvCode)) //Ici on parle du QStringList en attriburt
        return;

    uvCode = uvCode.toUpper();

    candidat->addItem(uvCode);
    candidats.append(uvCode);
}

void PredicatXUVParmis::delUv()
{
    QListWidget *candidat = sender()->parent()->findChild<QListWidget*>("candidat");
    if(!candidat)
        UTPROFILER_EXCEPTION("L'editeur de prédicat est corrompu");

    QList<QListWidgetItem*> selection = candidat->selectedItems();

    if(selection.isEmpty())
        return;

    for(auto it = selection.begin() ; it != selection.end() ; it++)
    {
        QListWidgetItem *item = *it;
        qDebug() << item->text();
        candidat->removeItemWidget(item);
        candidats.removeOne(item->text()); //TODO changer le nom de tout ça
    }
}

PredicatMinimumCreditInCategory::PredicatMinimumCreditInCategory() : Predicat(), minimum(0), cat(CS) {}
bool PredicatMinimumCreditInCategory::predicatSatifait(QVector<const UV *> uvValidee)
{
    unsigned int total = 0;

    for(auto it = uvValidee.begin() ; it != uvValidee.end() ; it++)
    {
        const UV* current = (*it);
        if(current->getCategorie() == cat)
            total += current->getNombreCredit();
    }

    return total >= minimum;
}
bool PredicatMinimumCreditInCategory::chargerParametres(QStringList &list)
{
    bool ok = true;

    cat = static_cast<CategorieUV>(list[0].toInt(&ok));
    if(!ok)
        return false;
    minimum = list[1].toInt(&ok);
    if(!ok)
        return false;

    return true;
}
void PredicatMinimumCreditInCategory::sauverParametre(QDomElement &elem)
{
    elem.setAttribute("type", PREDICAT_MINIMUM_CREDIT_IN_CATEGORY);
    QString param = QString::number(cat) + "," + QString::number(minimum);
    elem.setAttribute("param", param);
}

bool PredicatMinimumCreditInCategory::peutAmeliorerLeCursus(const QString &uv)
{
    UV *candidat = sUTManager->getUV(uv);

    if(!candidat)
        UTPROFILER_EXCEPTION(QString("UV inconnue : %1").arg(uv).toStdString().c_str());

    return cat == candidat->getCategorie();
}
QWidget* PredicatMinimumCreditInCategory::getEditorWidget(QWidget *parent)
{
    QWidget* container = new QWidget(parent);
    Ui_minimumCrediInCategory ui;
    ui.setupUi(container);

    for (unsigned int i=1; i<=NB_CATEGORIE; i++)
    {
        ui.cat->addItem(UTManager::categorieUVEnumToText(static_cast<CategorieUV>(i)), QVariant(i));
    }
    ui.cat->setCurrentText(UTManager::categorieUVEnumToText(cat));
    ui.credit->setValue(minimum);

    connect(ui.cat, SIGNAL(currentTextChanged(QString)), this, SLOT(updateCat(QString)));
    connect(ui.credit, SIGNAL(valueChanged(int)), this, SLOT(updateMinimum(int)));
    connect(this, SIGNAL(destroyed()), container, SLOT(deleteLater()));
    return container;
}

PredicatMinimumCredit::PredicatMinimumCredit() : Predicat(), minimum(0) {}
bool PredicatMinimumCredit::predicatSatifait(QVector<const UV *> uvValidee)
{
    unsigned int total = 0;

    for(auto it = uvValidee.begin() ; it != uvValidee.end() ; it++)
    {
        const UV* current = (*it);
        total += current->getNombreCredit();
    }

    return total >= minimum;
}
bool PredicatMinimumCredit::chargerParametres(QStringList &list)
{
    bool ok = true;
    minimum = list.first().toInt(&ok);
    if(!ok)
        return false;

    return true;
}
void PredicatMinimumCredit::sauverParametre(QDomElement &elem)
{
    elem.setAttribute("type", PREDICAT_MINIMUM_CREDIT);
    elem.setAttribute("param", minimum);
}
QWidget* PredicatMinimumCredit::getEditorWidget(QWidget *parent)
{
    QHBoxLayout *lay = new QHBoxLayout(parent);
    QSpinBox *spin = new QSpinBox(parent);
    QWidget* container = new QWidget(parent);

    connect(spin, SIGNAL(valueChanged(int)), this, SLOT(updateMinimum(int)));
    spin->setValue(minimum);
    spin->setMinimum(0);

    lay->addWidget(new QLabel("Crédit minimum : ", parent));
    lay->addWidget(spin);
    container->setLayout(lay);
    connect(this, SIGNAL(destroyed()), container, SLOT(deleteLater()));
    return container;
}

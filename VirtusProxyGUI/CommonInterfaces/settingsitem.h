#ifndef SETTINGS_H
#define SETTINGS_H

#include <QVariant>
#include <QString>

#include "commoninterfaces_global.h"

/*!
 *  class defining settings structure
 */
class COMMONINTERFACES_EXPORT SettingsItem
{
public:
    enum class Type:int
    {
        Unknown, Int, Double, Float, String, Ip, List, Bool, Port
    };
    /*!
      * \brief ����������� ������� ������ SettingsItem
      * �������������� ��� ����
      * ���������� ��-���������
      */
    SettingsItem();
    /*!
      * \brief ����������� ������� ������ SettingsItem
      * �������������� ��� �������� ����������� �����������
      */
    SettingsItem(QString name,QVariant value, Type type, double min, double max, double step, int precision);

    QVariantList listItems;
    QString     name;///<��� ���������
    QVariant    value;///<�������� ���������
    Type        type;///<��� ������ ���������
    double      min;///<����������� �������� ���������
    double      max;///<������������ �������� ���������
    double      step;///<���, � ������� ����� �������� ���������
    int         precision;///<����������� ����� �������
};

#endif // SETTINGS_H

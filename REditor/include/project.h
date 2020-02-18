#ifndef     PROJECT_H
#define     PROJECT_H

#include    <QObject>

class ProjectUnit;

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Project : public QObject
{
    Q_OBJECT

public:

    Project(QObject *parent = Q_NULLPTR);

    ~Project();

    /// Загрузка существующего проекта
    void load();

    /// Сохранение проекта
    void save();

    void setName(QString name);

    void setTitle(QString title);

    void setDescription(QString description);

    bool isChanged();

    QString getName() const;

    QString getTitle() const;

    QString getDescription() const;

private:

    /// Имя файла проекта
    QString     name;

    /// Заголовок проекта (например "Ростов - Горячий Ключ")
    QString     title;

    /// Описание проекта
    QString     description;

    /// Проект изменене
    bool        is_changed;

    /// Список частей проекта
    std::vector<ProjectUnit *>  units;
};

#endif // PROJECT_H

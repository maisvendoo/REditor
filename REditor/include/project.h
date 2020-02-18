#ifndef     PROJECT_H
#define     PROJECT_H

#include    <QObject>

class ProjectUnit;

class Profile;

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

    void setProjectDir(QString project_dir);

    bool isChanged();

    QString getName() const;

    QString getTitle() const;

    QString getDescription() const;

    Profile *getProfile();

private:

    /// Имя файла проекта
    QString     name;

    /// Заголовок проекта (например "Ростов - Горячий Ключ")
    QString     title;

    /// Описание проекта
    QString     description;

    /// Проект измененен
    bool        is_changed;

    /// Профиль (продольный и в плане)
    Profile     *profile;

    /// Директория с файлами проекта
    QString     project_dir;

    /// Список частей проекта
    std::vector<ProjectUnit *>  units;
};

#endif // PROJECT_H

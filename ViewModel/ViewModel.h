#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include "Common/Notification.h"
#include "Command/CalculateCommand.h"
#include "Command/RedoCommand.h"
#include "Command/UndoCommand.h"
#include "Model/Model.h"
#include <memory>

class ViewModel: public Proxy_Notification,
                 public INotification
{
public:
    ViewModel();
    ViewModel(shared_ptr<Model> p_model);
    void setModel(shared_ptr<Model> p_model);
    shared_ptr<Model>& getModel();
    shared_ptr<Data>& getPoints();
    void setPoints(shared_ptr<Data> p);

    shared_ptr<QString>& getInputString();
    shared_ptr<QString>& getOutputString();

    void update(const string& type);
    void setInputString(shared_ptr<QString> in);
    void setOutputString(shared_ptr<QString> out);

    void Calculate(string &in);
    void Redo();
    void Undo();

    shared_ptr<iCommand> getCalculateCommand();
    shared_ptr<iCommand> getRedoCommand();
    shared_ptr<iCommand> getUndoCommand();

    ~ViewModel(){}
private:
    shared_ptr<Model> pm;
    shared_ptr<QString> in, out;
    shared_ptr<Data> points;
    shared_ptr<iCommand> calculateCommand,redoCommand,undoCommand;
};

#endif // VIEWMODEL_H

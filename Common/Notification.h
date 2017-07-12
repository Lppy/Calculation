#pragma once
#include "Params.h"
#include <iostream>
using namespace std;

class INotification {
public:
    virtual void update(const string& type) = 0;
};

class NotificationImpl
{
public:
    vector<shared_ptr<INotification>>& GetNotificationArray(){
        return m_array;
    }
    void AddNotification(const shared_ptr<INotification>& p)
    {
        m_array.push_back(p);
    }
protected:
    vector<shared_ptr<INotification>> m_array;
};

class Proxy_Notification:public NotificationImpl {
public:
    Proxy_Notification(){}
    ~Proxy_Notification(){}
    void notify(const string& type){
        for(auto it=m_array.begin();it!=m_array.end();it++)
            (*it)->update(type);
    }
};

#ifndef TOKENMANAGER_H
#define TOKENMANAGER_H
#include <QString>

class TokenManager {
public:
    static TokenManager& getInstance() {
        static TokenManager instance;
        return instance;
    }
    void setToken(const QString& token) {
        m_token = token;
    }
    QString getToken() const {
        return m_token;
    }
private:
    TokenManager() {}
    QString m_token;
};

#endif // TOKENMANAGER_H

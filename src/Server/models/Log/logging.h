
#include "log_namespace.h"

class Logging{
protected:
    Logging(logging::LogInfo info): info_(info) {}

    //get method
    std::string getCreatedAt() { return info_.createdAt; }

private:
    const logging::LogInfo info_;

public:
    virtual void make_log() = 0;
    // virtual void get_logs() = 0;
};
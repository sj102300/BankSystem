
#include "file.grpc.pb.h"

class FileSystemManagerImpl : public file_system::FileSystemService::Service
{
private:
    std::shared_ptr<grpc::Channel> channel;
    std::unique_ptr<file_system::FileSystemService::Stub> stub;

public:
    FileSystemManagerImpl();
    ~FileSystemManagerImpl();
    grpc::Status ListAccountFiles(grpc::ServerContext *context, const file_system::account::ListAccountFilesRequest *request, file_system::account::ListAccountFilesResponse *response) override;
    grpc::Status GetAccountIntroFile(grpc::ServerContext *context, const file_system::account::GetAccountIntroFileRequest *request, file_system::account::GetAccountIntroFileResponse *response) override;
    grpc::Status GetAccountTermFile(grpc::ServerContext *context, const file_system::account::GetAccountTermFileRequest *request, file_system::account::GetAccountTermFileResponse *response) override;
};
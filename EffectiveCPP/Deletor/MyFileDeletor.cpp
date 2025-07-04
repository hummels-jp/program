#include <cstdio>
#include <iostream>
#include <memory>
using namespace std;

void close_file(FILE* f)
{
    cout << "function close_file " << endl;
    fclose(f); 
    f = nullptr;
}

struct CloseFileDeletor
{
    void operator()(FILE* f)
    {
        cout << "struct CloseFile" << endl;
        fclose(f);
    }

};

int main()
{
    FILE* fp = fopen("test.txt", "w");

    {
        // unique_ptr<FILE> up1(fp);

        // unique_ptr<FILE, void(*)(FILE*)> up2(fp, close_file);

        // unique_ptr<FILE, CloseFileDeletor> up3(fp, CloseFileDeletor{});

        auto lambda_file_deletor = [](FILE* f)->void
        {
            cout << "lambda_file_deletor " << endl;
            fclose(f);
        };
        unique_ptr<FILE, decltype(lambda_file_deletor)> up4(fp, lambda_file_deletor);
    }
    

}
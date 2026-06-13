#include "NetworkHandler.h"

int main() 
{
    printf(
        "$$$$$$$$\\  $$$$$$\\                   \n"
        "\\__$$  __|$$  __$$\\ $$\\       $$\\    \n"
        "   $$ |   $$ /  \\__|$$ |      $$ |   \n"
        "   $$ |   $$ |   $$$$$$$$\\ $$$$$$$$\\ \n"
        "   $$ |   $$ |   \\__$$  __|\\__$$  __|\n"
        "   $$ |   $$ |  $$\\ $$ |      $$ |   \n"
        "   $$ |   \\$$$$$$  |\\__|      \\__|   \n"
        "   \\__|    \\______/                  \n"
        "\n"
        "\n"
    );

    auto& NetworkObject = NetworkHandler::GetInstance();

    NetworkObject.InitializeWinsock();
    NetworkObject.CreateServer();
}
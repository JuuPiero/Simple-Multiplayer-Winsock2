#include "Application.h"
#include "Utils.h"
#include "Entry.h"
#include "ServerApplication.h"

Shared<JuuPiero::Application> CreateApplication() {
    JuuPiero::ApplicationProperties props;
    props.Width = WINDOW_WIDTH;
    props.Height = WINDOW_HEIGHT;
    props.Title = "Native Window";
    props.Platform = JuuPiero::WindowPlatform::SDL;
    return std::make_shared<JuuPiero::ServerApplication>(props);
}
#include "Application.h"
#include "Utils.h"
#include "Entry.h"
#include "Sanbox.h"



Shared<JuuPiero::Application> CreateApplication() {
    auto props = JuuPiero::ApplicationProperties();
    props.Width = WINDOW_WIDTH;
    props.Height = WINDOW_HEIGHT;
    props.Title = "Native Window";
    props.Platform = JuuPiero::WindowPlatform::SDL;
    return std::make_shared<Sanbox>(props);
}
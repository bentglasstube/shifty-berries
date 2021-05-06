#pragma once

#include <memory>

#include "backdrop.h"
#include "graphics.h"
#include "input.h"
#include "screen.h"
#include "text.h"

class FinishScreen : public Screen {
  public:
    void init();
    bool update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed);
    void draw(Graphics& graphics);

    Screen* next_screen();
    std::string get_music_track() { return ""; }

    void set_results(int _time, int _deaths);

  private:

    int time, deaths;
    bool retry;
    std::unique_ptr<Backdrop> backdrop;
    std::unique_ptr<Text> text;
};

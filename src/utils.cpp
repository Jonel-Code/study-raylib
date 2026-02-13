#define LOGDELTA(Message)             \
    static float AccuDelta = 0;       \
    AccuDelta += GetFrameTime();      \
    if (AccuDelta > 1)                \
    {                                 \
        AccuDelta = 0;                \
        std::cout << Message << '\n'; \
    }
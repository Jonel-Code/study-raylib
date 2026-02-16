#define LOGDELTA(Message)             \
    static float AccuDelta = 0;       \
    AccuDelta += GetFrameTime();      \
    if (AccuDelta > 1)                \
    {                                 \
        AccuDelta = 0;                \
        std::cout << Message << '\n'; \
    }

#define SINGELTON(Type)             \
    static Type *Instance()         \
    {                               \
        static Type *singleton;     \
        if (singleton == nullptr)   \
        {                           \
            singleton = new Type(); \
        }                           \
        return singleton;           \
    }

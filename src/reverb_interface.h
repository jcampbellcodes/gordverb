namespace gordverb
{
    template <typename EarlyReflections, typename LateReflections>
    class ReverbInterface
    {
            void SetReverbTimeMs( float inReverbTimeMs );
            void SetWetAmount( float inWet );
        private:
            EarlyReflections mEarlyReflections;
            LateReflections mLateReflections;
    };
}
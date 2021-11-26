namespace juce
{
namespace dsp
{
    
    /**
     Represents an increasing phase value between 0 and 2*pi.
     
     This represents a value which can be incremented, and which wraps back to 0 when it
     goes past 2 * pi.
     
     @tags{DSP}
     */
    template <typename Type>
    struct EndlessPhase
    {
        /** Resets the phase to 0. */
        void reset() noexcept               { phase = 0; }
        
        /** Returns the current value, and increments the phase by the given increment.
         The increment must be a positive value, it can't go backwards!
         The new value of the phase after calling this function will be (phase + increment) % (2 * pi).
         */
        Type advance (Type increment) noexcept
        {
            jassert (increment >= 0); // cannot run this value backwards!
            
            auto last = phase;
            auto next = last + increment;
            
            auto maxPhase = maxRotations * juce::MathConstants<float>::twoPi;
            
            while (next >= maxPhase)
                next -= maxPhase;
            
            phase = next;
            return last;
        }
        
        Type phase = 0;
        Type maxRotations = 100;
    };
    
} // namespace dsp
} // namespace juce

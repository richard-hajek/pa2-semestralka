#ifndef SEMESTER_PROJECT_ROUNDS_H
#define SEMESTER_PROJECT_ROUNDS_H
#include "Fragment.h"

/**
 * System to take care of increasing difficulty, spawning enemies
 */
class Rounds final : public Fragment {
public:

    /**
     * Construct this system
     * @param game Parent game
     */
    explicit Rounds(Game * game);

    /**
     * Request a small window
     * @param width request window width
     * @param height request window height
     */
    void RequestDimensions(int & width, int & height) final;

    /**
     * Load current round and possibly timeout
     * @param reader reader of the save file, ready to read wave data
     * @return true on success
     */
    bool Load(TSVReader & reader) final;

    /**
     * Save this Round data to TSVWriter
     * @param writer Writer to write to
     * @return true on success
     */
    bool Save(TSVWriter & writer) final;

    void Ready() final;

    void Update(double delta) final;

    /**
     * Render all wave hint
     */
    void Render() final;

    /**
     * Free resources
     */
    ~Rounds() final;

    /**
     * @return true if game currently in prepare stage
     */
    bool IsPrepareStage();

    /**
     * Run to skip wait and/or kill all enemies
     */
    void DebugSkipWait();

    /**
     * @return the current round count
     */
    int GetRound();

    /**
     * @return the current prepare timeout
     */
    double GetPrepareTimeout();

    /**
     * @return the amount of enemies yet to spawn
     */
    int GetToSpawn();

private:

    /// Current round
    int m_Round = 0;

    /// Timeout in between levels
    double m_PrepareTimeout = 0;
    bool m_PrepareStage = false;

    /// Timeout in between levels
    bool m_GameStage = false;
    int m_ToSpawn = 0;

};

#endif //SEMESTER_PROJECT_ROUNDS_H

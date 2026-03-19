namespace Raycaster;

public static class GameLogic
{
    /// <summary>
    /// Avance le timer de survie et incrémente le score d'1 par seconde écoulée.
    /// Retourne true si le score a changé (au moins +1) sur ce tick.
    /// </summary>
    public static bool AdvanceSurvival(ref float survivalTimer, ref int score, float deltaTimeSeconds)
    {
        if (deltaTimeSeconds <= 0f)
            return false;

        survivalTimer += deltaTimeSeconds;

        int gained = (int)(survivalTimer / 1.0f);
        if (gained <= 0)
            return false;

        score += gained;
        survivalTimer -= gained * 1.0f;
        return true;
    }
}


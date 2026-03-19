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

    /// <summary>
    /// Tente de ramasser le couteau si il est sur la carte et que la distance est sous le seuil.
    /// Retourne true si le ramassage a réussi et met à jour hasKnife / isKnifeSpawned.
    /// </summary>
    public static bool TryPickupKnife(ref bool hasKnife, ref bool isKnifeSpawned, float distanceToKnife, float pickupThreshold)
    {
        if (!isKnifeSpawned || distanceToKnife >= pickupThreshold)
            return false;
        hasKnife = true;
        isKnifeSpawned = false;
        return true;
    }

    /// <summary>
    /// Tente d'utiliser le couteau (attaque). Consomme l'arme et retourne true si le joueur avait le couteau et que l'input d'attaque est pressé.
    /// </summary>
    public static bool TryUseKnife(ref bool hasKnife, bool isAttackInputPressed)
    {
        if (!hasKnife || !isAttackInputPressed)
            return false;
        hasKnife = false;
        return true;
    }
}


using Xunit;

namespace Raycaster.Tests;

public class GameLogicTests
{
    [Fact]
    public void TryPickupKnife_Succeeds_WhenDistanceValidAndKnifePresent()
    {
        bool hasKnife = false;
        bool isKnifeSpawned = true;
        float distanceToKnife = 10f;
        float pickupThreshold = 32f;

        bool result = Raycaster.GameLogic.TryPickupKnife(ref hasKnife, ref isKnifeSpawned, distanceToKnife, pickupThreshold);

        Assert.True(result);
        Assert.True(hasKnife);
        Assert.False(isKnifeSpawned);
    }

    [Fact]
    public void TryPickupKnife_Fails_WhenDistanceTooLarge()
    {
        bool hasKnife = false;
        bool isKnifeSpawned = true;
        float distanceToKnife = 100f;
        float pickupThreshold = 32f;

        bool result = Raycaster.GameLogic.TryPickupKnife(ref hasKnife, ref isKnifeSpawned, distanceToKnife, pickupThreshold);

        Assert.False(result);
        Assert.False(hasKnife);
        Assert.True(isKnifeSpawned);
    }

    [Fact]
    public void TryUseKnife_Succeeds_WhenPlayerHasKnifeAndInputPressed()
    {
        bool hasKnife = true;
        bool isAttackInputPressed = true;

        bool result = Raycaster.GameLogic.TryUseKnife(ref hasKnife, isAttackInputPressed);

        Assert.True(result);
        Assert.False(hasKnife);
    }

    [Fact]
    public void TryUseKnife_Fails_WhenInputPressedButPlayerHasNoKnife()
    {
        bool hasKnife = false;
        bool isAttackInputPressed = true;

        bool result = Raycaster.GameLogic.TryUseKnife(ref hasKnife, isAttackInputPressed);

        Assert.False(result);
        Assert.False(hasKnife);
    }
}

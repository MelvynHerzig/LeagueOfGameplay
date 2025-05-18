// Herzig Melvyn - League of Gameplay

#include "Players/Camera/LgpCamera.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/MathFwd.h"


// Sets default values
ALgpCamera::ALgpCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set up the camera
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	RootComponent = SpringArmComponent;
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = 700.f;
	SpringArmComponent->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmTargetLength = SpringArmComponent->TargetArmLength;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
}

void ALgpCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// --------------------- Camera translation ---------------------
	static FVector2d MousePosition = FVector2d::ZeroVector;
	static FVector2d ViewPortSize = FVector2d::ZeroVector;
	static const FVector2d SensitiveZoneDimensions = FVector2d(100.f, 100.f);
	static const FVector CameraMovementSpeed = FVector(-1000.f, 1000.f, 0.f);

	if (LockedActor.IsValid())
	{
		SetActorLocation(LockedActor->GetActorLocation());
	}
	else
	{
		MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
		ViewPortSize = UWidgetLayoutLibrary::GetViewportWidgetGeometry(this).GetLocalSize();
	
	
		// Check if mouse position is inside the zone of the viewport where we need to move the camera.
		// The viewport moving zone is 100 unit top/bottom/left/right.
		// Given:
		// Mouse position with origin in the middle: MousePosition - ViewPortSize * 0.5f
		// The half of the "dead zone": (ViewPortSize - 2 * SensitiveZoneDimensions) / 2
		// If the mouse position / half of the dead zone > 1 (or < -1), we need to move the camera., 
		MousePosition = (MousePosition - ViewPortSize * 0.5f) / ((ViewPortSize - 2 * SensitiveZoneDimensions) / 2) ;
		MousePosition.X = static_cast<int>(MousePosition.X);
		MousePosition.Y = static_cast<int>(MousePosition.Y);
		MousePosition.Normalize();

		AddActorWorldOffset(CameraMovementSpeed * UKismetMathLibrary::Conv_Vector2DToVector({MousePosition.Y, MousePosition.X}, 0) * DeltaTime);	
	}

	// --------------------- Camera Zoom ---------------------
	SpringArmComponent->TargetArmLength = FMath::FInterpTo(
		SpringArmComponent->TargetArmLength,
		SpringArmTargetLength,
		DeltaTime,
		10.f
	);
}

void ALgpCamera::Follow(APawn* Target)
{
	LockedActor = Target;
	// We don't want to be off by one frame so wait that movement component ticks.
	UPawnMovementComponent* PawnMovement = Target->GetMovementComponent();
	if (PawnMovement && PawnMovement->PrimaryComponentTick.bCanEverTick)
	{
		PrimaryActorTick.AddPrerequisite(PawnMovement, PawnMovement->PrimaryComponentTick);
	}
}

void ALgpCamera::StopFollow()
{
	if (LockedActor.IsValid())
	{
		UPawnMovementComponent* PawnMovement = LockedActor->GetMovementComponent();
		if (PawnMovement && PawnMovement->PrimaryComponentTick.bCanEverTick)
		{
			PrimaryActorTick.RemovePrerequisite(PawnMovement, PawnMovement->PrimaryComponentTick);
		}
	}
	
	LockedActor.Reset();
}

void ALgpCamera::Zoom(float Offset)
{
	SpringArmTargetLength = FMath::Clamp(SpringArmComponent->TargetArmLength - Offset * 50, 300.f, 700.f);
}

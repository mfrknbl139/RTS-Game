#include "SPlayerPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Microsoft/AllowMicrosoftPlatformTypes.h"

ASPlayerPawn::ASPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent=SceneComponent;

	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength=2000.0f;
	SpringArmComponent->bDoCollisionTest=false;

	CameraComponent=CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}
void ASPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	TargetLocation=GetActorLocation();
	TargetZoom=3000.f;

	const FRotator Rotation=SpringArmComponent->GetRelativeRotation();
	TargetRotation=FRotator(Rotation.Pitch+-50,Rotation.Yaw,0.0f);
}
void ASPlayerPawn::Forward(float AxisValue)
{
	if (AxisValue==0.f)
	{
		return;
	}
	TargetLocation=SpringArmComponent->GetForwardVector() * AxisValue * MoveSpeed + TargetLocation;
}
void ASPlayerPawn::Right(float AxisValue)
{
	if (AxisValue==0.f)
	{
		return;
	}
	TargetLocation=SpringArmComponent->GetRightVector() * AxisValue * MoveSpeed + TargetLocation;
}
void ASPlayerPawn::Zoom(float AxisValue)
{
	if (AxisValue == 0.f)
	{
		return;
	}
	const float Zoom=AxisValue*100.f;
	TargetZoom=FMath::Clamp(Zoom+TargetZoom,MinZoom,MaxZoom);
}
void ASPlayerPawn::RotateRight()
{
	TargetRotation= UKismetMathLibrary::ComposeRotators(TargetRotation,FRotator(0.0f,-45,0.0f));
}
void ASPlayerPawn::RotateLeft()
{
	TargetRotation= UKismetMathLibrary::ComposeRotators(TargetRotation,FRotator(0.0f,45,0.0f));
}
void ASPlayerPawn::EnableRotate()
{
	CanRotate=true;
}
void ASPlayerPawn::DisableRotate()
{
	CanRotate=false;
}
void ASPlayerPawn::RotateHorizontal(float AxisValue)
{
	if(AxisValue==0.f)
	{
		return;
	}
	if(CanRotate)
	{
		TargetRotation=UKismetMathLibrary::ComposeRotators(TargetRotation,FRotator(0.f,AxisValue,0.f));
	}
}
void ASPlayerPawn::RotateVertical(float AxisValue)
{
	if (AxisValue==0.f)
	{
		return;
	}
	if(CanRotate)
	{
		TargetRotation=UKismetMathLibrary::ComposeRotators(TargetRotation,FRotator(AxisValue,0.f,0.f));
	}
}
void ASPlayerPawn::CameraBounds()
{
	float NewPitch=TargetRotation.Pitch;
	if (TargetRotation.Pitch<(RotatePitchMax * -1))
	{
		NewPitch=(RotatePitchMax * -1);
	}
	else if(TargetRotation.Pitch>(RotatePitchMin * -1))
	{
		NewPitch=(RotatePitchMin*-1);
	}

	TargetRotation=FRotator(NewPitch,TargetRotation.Yaw,0.f);
	TargetLocation=FVector(TargetLocation.X,TargetLocation.Y,0.f);
}
void ASPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CameraBounds();
	
	const FVector InterpolatedLoc= UKismetMathLibrary::VInterpTo(GetActorLocation(),TargetLocation,DeltaTime,MoveSpeed);
	SetActorLocation(InterpolatedLoc);

	const float InterpolatedZoom=UKismetMathLibrary::FInterpTo(SpringArmComponent->TargetArmLength,TargetZoom,DeltaTime,ZoomSpeed);
	SpringArmComponent->TargetArmLength=InterpolatedZoom;

	const FRotator InterpolatedRotation=UKismetMathLibrary::RInterpTo(SpringArmComponent->GetRelativeRotation(),TargetRotation,DeltaTime,RotateSpeed);
	SpringArmComponent->SetRelativeRotation(InterpolatedRotation);
}
void ASPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(TEXT("Forward"),this,&ASPlayerPawn::Forward);
	PlayerInputComponent->BindAxis(TEXT("Right"),this,&ASPlayerPawn::Right);
	PlayerInputComponent->BindAxis(TEXT("Zoom"),this,&ASPlayerPawn::Zoom);
	PlayerInputComponent->BindAxis(TEXT("RotateHorizontal"),this,&ASPlayerPawn::RotateHorizontal);
	PlayerInputComponent->BindAxis(TEXT("RotateVertical"),this,&ASPlayerPawn::RotateVertical);

	PlayerInputComponent->BindAction(TEXT("RotateRight"),IE_Pressed,this,&ASPlayerPawn::RotateRight);
	PlayerInputComponent->BindAction(TEXT("RotateLeft"),IE_Pressed,this,&ASPlayerPawn::RotateLeft);
	PlayerInputComponent->BindAction(TEXT("Rotate"),IE_Pressed,this,&ASPlayerPawn::EnableRotate);
	PlayerInputComponent->BindAction(TEXT("Rotate"),IE_Pressed,this,&ASPlayerPawn::DisableRotate);
}


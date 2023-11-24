#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "SPlayerPawn.generated.h"


class USpringArmComponent;

UCLASS()
class RTS_API ASPlayerPawn : public APawn
{
	GENERATED_BODY()
public:
	ASPlayerPawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	UFUNCTION()
	void Forward(float AxisValue);
	UFUNCTION()
	void Right(float AxisValue);
	UFUNCTION()
	void Zoom(float AxisValue);
	UFUNCTION()
	void RotateRight();
	UFUNCTION()
	void RotateLeft();
	UFUNCTION()
	void EnableRotate();
	UFUNCTION()
	void DisableRotate();
	UFUNCTION()
	void RotateHorizontal(float AxisValue);
	UFUNCTION()
	void RotateVertical(float AxisValue);
	
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings|Camera")
	float MoveSpeed = 20.0f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Settings|Camera")
	float RotateSpeed=2.0f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Settings|Camera")
	float RotatePitchMin=10.0f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Settings|Camera")
	float RotatePitchMax=80.0f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Settings|Camera")
	float ZoomSpeed=25.0f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Settings|Camera")
	float MinZoom=100.0f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Settings|Camera")
	float MaxZoom=50000.0f;

private:
	UFUNCTION()
	void CameraBounds();
	
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,meta=(AllowPrivateAccess="true"))
	USceneComponent* SceneComponent;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,meta=(AllowPrivateAccess="true"))
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,meta=(AllowPrivateAccess="true"))
	UCameraComponent* CameraComponent;
	UPROPERTY()
	FVector TargetLocation;
	UPROPERTY()
	FRotator TargetRotation;
	UPROPERTY()
	float TargetZoom;
	UPROPERTY()
	bool CanRotate;
};

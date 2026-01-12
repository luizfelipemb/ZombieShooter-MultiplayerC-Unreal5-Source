// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "SActionComponent.h"
#include "SWeapon.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->SetWorldRotation(FRotator(-30.0f, 0.0f, 0.0f));
	SpringArmComp->TargetArmLength = 700;
	SpringArmComp->bUsePawnControlRotation = false;
	SpringArmComp->bInheritPitch = false;
	SpringArmComp->bInheritRoll = false;
	SpringArmComp->bInheritYaw = false;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComp);

	AttributeComp = CreateDefaultSubobject<USAttributesComponent>("Attributes");
	XpAttributeComp = CreateDefaultSubobject<USXpAttribute>("XpAttribute");
	UpgradesManagerComp = CreateDefaultSubobject<USUpgradesManager>("UpgradesManager");
	WeaponsManagerComp = CreateDefaultSubobject<USWeaponsManager>("WeaponsManager");
	WeaponsManagerComp->Init(GetMesh());
	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComponent");
	ActionComp = CreateDefaultSubobject<USActionComponent>("ActionComponent");
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	bUseControllerRotationYaw = false;
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);
	
	PlayerInputComponent->BindAction("PrimaryAttack",IE_Pressed,this,&ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryAttack",IE_Released,this,&ASCharacter::PrimaryAttackRelease).bExecuteWhenPaused = true;;
	PlayerInputComponent->BindAction("PrimaryInteract",IE_Pressed,this,&ASCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ASCharacter::Reload);
	PlayerInputComponent->BindAction("SelectWeapon1", IE_Pressed, this, &ASCharacter::SelectWeapon1);
	PlayerInputComponent->BindAction("SelectWeapon2", IE_Pressed, this, &ASCharacter::SelectWeapon2);
	PlayerInputComponent->BindAction("SelectWeapon3", IE_Pressed, this, &ASCharacter::SelectWeapon3);
	PlayerInputComponent->BindAction("SelectWeapon4", IE_Pressed, this, &ASCharacter::SelectWeapon4);

	PlayerInputComponent->BindAction("HackXP", IE_Pressed, this, &ASCharacter::HackXP);
}

void ASCharacter::HackXP()
{
	if (XpAttributeComp)
	{
		XpAttributeComp->AddXp(XpAttributeComp->GetMaxXpParam());
	}
}

void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	WeaponsManagerComp->SwitchWeapon(0);
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// Get the camera's forward vector
		FRotator CameraRot = CameraComp->GetComponentRotation();
		CameraRot.Pitch = 0.0f;  // Ignore the pitch to prevent moving up/down with camera's pitch
        
		FVector ForwardVector = FRotationMatrix(CameraRot).GetScaledAxis(EAxis::X);
		AddMovementInput(ForwardVector, Value);
	}
}

void ASCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// Get the camera's right vector
		FRotator CameraRot = CameraComp->GetComponentRotation();
		CameraRot.Pitch = 0.0f;  // Ignore the pitch to prevent moving up/down with camera's pitch
        
		FVector RightVector = FRotationMatrix(CameraRot).GetScaledAxis(EAxis::Y);
		AddMovementInput(RightVector, Value);
	}
}

void ASCharacter::PrimaryAttack()
{
	WeaponsManagerComp->ShootingButtonPressed();
}
void ASCharacter::PrimaryAttackRelease()
{
	WeaponsManagerComp->ShootingButtonReleased();
}
void ASCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}


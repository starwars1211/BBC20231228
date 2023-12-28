// Fill out your copyright notice in the Description page of Project Settings.


#include "BB_Character.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"


// Sets default values
ABB_Character::ABB_Character()
{
	

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule , "Components/CapsuleComponent.h"

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent)
		;
	/*
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	// Configure character movement ,  "GameFramework/CharacterMovementComponent.h"
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;
	
	// Create a camera boom (pulls in towards the player if there is a collision), "GameFramework/SpringArmComponent.h"
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera //"Camera/CameraComponent.h"
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	*/
}



// Called when the game starts or when spawned
void ABB_Character::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();

	//Add Input Mapping Context

	
}

// Called every frame
void ABB_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABB_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast< UEnhancedInputComponent>(PlayerInputComponent))
	{
		//jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::StopJumping);
		//Move
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &ABB_Character::Move);
		//Look
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Started, this, &ABB_Character::Look);
		//Action left mouse
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ABB_Character::Action);
		//Equip
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Started, this, &ABB_Character::Equip);

	}
	/*
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
	*/
	
}

void ABB_Character::Move(const FInputActionValue& Value)
{
	
	//Input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		//fine out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotarion(0, Rotation.Yaw, 0);

		//get foward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotarion).GetUnitAxis(EAxis::X);
		//get right vector
		const FVector RightDirection = FRotationMatrix(YawRotarion).GetUnitAxis(EAxis::Y);

		//add movement
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}

	
}

void ABB_Character::Look(const FInputActionValue& Value)
{

}

void ABB_Character::Action(const FInputActionValue& Value)
{

}

void ABB_Character::Equip(const FInputActionValue& Value)
{

}
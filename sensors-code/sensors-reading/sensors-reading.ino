#include <DHT.h>

// Définition du type de capteur et de la broche à laquelle il est connecté
#define DHTPIN 2     // Broche digitale utilisée pour le capteur DHT11
#define DHTTYPE DHT11   // Type de capteur DHT utilisé (DHT11)

// Initialisation du capteur DHT
DHT dht(DHTPIN, DHTTYPE);

// Broche digitale utilisée pour la LED
#define LED_PIN 13

void setup() {
  Serial.begin(9600); // Initialisation de la communication série
  pinMode(LED_PIN, OUTPUT); // Configuration de la broche de la LED en mode sortie
  dht.begin(); // Initialisation du capteur DHT
}

void loop() {
  // Lecture de l'humidité relative
  float humidity = dht.readHumidity();
  // Lecture de la température en Celsius
  float temperature = dht.readTemperature();

  // Vérification si la lecture a réussi
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Erreur lors de la lecture du capteur DHT !");
    delay(2000);
    return;
  }

  // Allumage de la LED jaune pour indiquer l'envoi des données
  digitalWrite(LED_PIN, LOW);
  
  // Envoi des données via la communication série
  Serial.print("H:");
  Serial.print(humidity);
  Serial.print(", T:");
  Serial.println(temperature);

  // Attente d'une seconde pour laisser le temps à la LED de rester allumée
  delay(1000);
  
  // Extinction de la LED jaune
  digitalWrite(LED_PIN, HIGH);

  // Attente de quelques secondes avant de lire à nouveau les données
  delay(2000);
}

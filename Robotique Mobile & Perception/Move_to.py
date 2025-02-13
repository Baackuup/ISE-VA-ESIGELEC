from math import atan2, degrees
from robomaster import robot
import time

class RobotNavigator:
    def __init__(self, robot):
        self.robot = robot
        self.ep_sensor = self.robot.sensor
        # Initialisation des variables pour mesure distance
        self.distance_sub = None
        self.last_distances = []
        
        #def position robot et destination
        self.position_robot = {'X': 0, 'Y': 0, 'Z': 0}
        self.destination = None

        #directio_evitement ==-1 corespond à gauche, directio_evitement ==1 corespond à droit, 
        self.direction_evitement = -1
        self.angle_rotat =90
        self.vitesse_translate = 1.5
        self.vitesse_rotate = 3



    def get_robot_destination(self):
        x_dest = float(input("Entrez la coordonnée X de la zone B (en mètre) : "))
        y_dest = float(input("Entrez la coordonnée Y de la zone B (en mètre) : "))
        self.destination = {'X': x_dest, 'Y': y_dest}
    
    def move_forwarde(self, move_distance):
        self.robot.chassis.move(x=move_distance, y=0, z=0, xy_speed=self.vitesse_translate).wait_for_completed()
        
    def move_transverse(self, move_distance):
        self.robot.chassis.move(x=0, y=move_distance, z=0, xy_speed=0.7).wait_for_completed()
    
    def move_rotate(self, move_distance):
        self.robot.chassis.move(x=0, y=0, z=move_distance, xy_speed=self.vitesse_rotate).wait_for_completed()
        


    def update_position_x(self, move_distance):
        self.position_robot['X'] = self.position_robot['X'] + move_distance

    def update_position_y(self, move_distance):
        self.position_robot['Y'] = self.position_robot['Y'] + move_distance

    def update_position_z(self,move_distance):
        self.position_robot['Z'] = self.position_robot['Z'] + move_distance





    def move_to_destination(self):
        step_distance = 0.3
        while self.position_robot['X'] < self.destination['X']:
            if self.detect_obstacle(0, 500):
                self.evite_obstacle()
            else:
                self.move_forwarde(step_distance)
                self.update_position_x(step_distance)
                


    def detect_obstacle(self, sensor_number, threshold_distance):

        self.enable_infrared_distance_measurement()

        # Attendre jusqu'à ce que les données de distance soient disponibles

        time.sleep(0.3)  # Attendre 10 millisecondes entre chaque tentative
                # Obtenir la dernière distance mesurée par le capteur infrarouge
        distances_mesurees = self.get_infrared_distance()
        print(f"Distances mesurées par le capteur infrarouge : {distances_mesurees}")

        # Désactiver la mesure de distance infrarouge
        self.disable_infrared_distance_measurement()

        # Vérification si la distance du capteur est inférieure à la distance seuil
        return distances_mesurees[sensor_number] < threshold_distance

    #mesure la distance
    def enable_infrared_distance_measurement(self):
        """Active la mesure de distance infrarouge."""
        self.distance_sub = self.ep_sensor.sub_distance(freq=5, callback=self.distance_callback)

    def disable_infrared_distance_measurement(self):
        """Désactive la mesure de distance infrarouge."""
        if self.distance_sub:
            self.ep_sensor.unsub_distance()

    def distance_callback(self, distances):
        """Callback appelé lors de la réception des données de distance."""
        self.last_distances = distances

    def get_infrared_distance(self):
        """Obtient la dernière distance mesurée par le capteur infrarouge."""
        return self.last_distances




    def evite_obstacle(self):
        distance_detect = 500
        distance_deplacement = 0.6
        #choix de la directions optimale

        while True:
            obstacle_1 = False
            obstacle_2 = False
            #tourne de 90 dans une directions et controle si obstacle
            self.move_rotate(self.direction_evitement * self.angle_rotat)
            if self.detect_obstacle( 0, distance_detect):
                #enregistrement de l'obstacle
                obstacle_1 = True
                self.direction_evitement = -self.direction_evitement
                print("il y a un obstacle_1")
            else:
                self.move_forwarde(distance_deplacement)
                self.update_position_y(self.direction_evitement * distance_deplacement)
                self.move_rotate(-self.direction_evitement * self.angle_rotat)
                break

            if obstacle_1 == True:
                self.move_rotate(self.direction_evitement* 2 * self.angle_rotat)
                if self.detect_obstacle( 0, distance_detect):
                    #enregistrement de l'obstacle
                    obstacle_2 = True
                    print("il y a un obstacle_2")
                else:
                    self.move_forwarde(distance_deplacement)
                    self.update_position_y(-self.direction_evitement * distance_deplacement)
                    self.move_rotate(-self.direction_evitement * self.angle_rotat)
                    break
            
            if obstacle_2 == True:
                self.move_rotate(-self.direction_evitement * self.angle_rotat)
                self.move_forwarde(-distance_deplacement)
                self.update_position_x(-distance_deplacement)
            else:
                print("casnon possible, il y a un bug")



if __name__ == '__main__':
    # Initialiser le robot
    ep_robot = robot.Robot()
    ep_robot.initialize(conn_type="ap")

    # Créer une instance de RobotNavigator
    navigator = RobotNavigator(ep_robot)

    # Obtenir les coordonnées de destination de l'utilisateur
    navigator.get_robot_destination()

    navigator.move_to_destination()


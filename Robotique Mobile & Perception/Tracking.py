import math
from robomaster import robot, chassis, vision, camera
import time

class PersonFollower:

    def __init__(self, robot, target_distance=1.5):
        self.robot = robot
        self.target_distance = target_distance
        self.persons = []

        # Utiliser la résolution prédéfinie de la caméra (720P)
        self.image_width, self.image_height = 1280, 720

        # Démarrer le flux vidéo avec une résolution spécifique
        self._initialize_camera()

        # Initialiser le châssis
        self.chassis = chassis.Chassis(self.robot)

        # S'abonner à la détection de personnes
        self._subscribe_person_detection()

    def _initialize_camera(self):
        """Initialise la caméra avec la résolution spécifiée."""
        resolution = (self.image_width, self.image_height)
        self.robot.camera.start_video_stream(display=True, resolution=resolution)

    def _subscribe_person_detection(self):
        """S'abonne à la détection de personnes."""
        self.robot.vision.sub_detect_info(name="person", callback=self.on_detect_person)

    def on_detect_person(self, person_info):
        """Callback appelé lors de la détection de personnes."""
        self.persons.clear()
        for i in range(len(person_info)):
            x, y, w, h = person_info[i]
            self.persons.append(PersonInfo(x, y, w, h, self))

    def calculate_distance(self, person):
        pixel_width_of_person = person.pt2[0] - person.pt1[0]
        real_width_of_person = 0.6  # Adjust based on the actual width of the person
        real_width_of_calibration_object = 0.07
        distance_to_calibration_object = 0.2
        pixel_width_of_calibration_object = 210
        distance_focale = (pixel_width_of_calibration_object * distance_to_calibration_object) / real_width_of_calibration_object
        distance_to_object = (real_width_of_person * distance_focale) / pixel_width_of_person
        return distance_to_object

    def calculate_angle(self, person, distance):
        # Utiliser person.center au lieu de person_position
        relative_position_pix = person.center[0] - self.image_width / 2
        print("relative_position_pix :", relative_position_pix)
        print("pt1 :", person.pt1)
        print("pt2 :", person.pt2)

        # Éviter une division par zéro
        if relative_position_pix != 0:
            real_width_of_person = 0.6
            relativ_width_of_person = person.pt2[0]-person.pt1[0]
            ratio_pix_metre = real_width_of_person / relativ_width_of_person
            relative_position_metre = ratio_pix_metre * relative_position_pix

            # Calcul de l'angle en radians
            angle_radians = math.atan2(relative_position_metre, distance)

            # Conversion de l'angle en degrés
            angle_degrees = math.degrees(angle_radians)

            return angle_degrees
        else:
            return 0.0  # Valeur par défaut si relative_position_pix est égal à zéro


    def follow_person(self):
        try:
            while True:
                time.sleep(0.05)

                if self.persons:
                    person = self.persons[0]

                    # Calculer la distance et l'angle à la personne détectée
                    distance = self.calculate_distance(person)
                    angle = self.calculate_angle(person,distance)

                    # Calculer la différence entre la distance cible et la distance actuelle
                    distance_difference = distance - self.target_distance

                    # Régler la vitesse du châssis en fonction de la différence de distance
                    speed = 1.4 * distance_difference  # Ajuster la vitesse en fonction des besoins

                    # Régler la direction du châssis en fonction de l'angle
                    rotation_speed = 2 * angle  # Ajuster la vitesse de rotation en fonction des besoins

                    # Régler la vitesse du châssis pour suivre la personne
                    self.chassis.drive_speed(x=speed, z=rotation_speed)

                else:
                    # Si aucune personne n'est détectée, arrêter le châssis
                    self.chassis.drive_speed(x=0, z=0)

        except KeyboardInterrupt:
            print("Interruption clavier. Arrêt du suivi.")
        finally:
            # Se désabonner de la détection de personnes
            self.robot.vision.unsub_detect_info(name="person")
            # Arrêter le flux vidéo
            self.robot.camera.stop_video_stream()
            # Fermer la connexion au robot
            self.robot.close()


class PersonInfo:
    def __init__(self, x, y, w, h, person_detector):
        self._x = x
        self._y = y
        self._w = w
        self._h = h
        self.person_detector = person_detector

    @property
    def image_width(self):
        return self.person_detector.image_width

    @property
    def image_height(self):
        return self.person_detector.image_height

    @property
    def pt1(self):
        return int((self._x - self._w / 2) * self.image_width), int((self._y - self._h / 2) * self.image_height)

    @property
    def pt2(self):
        return int((self._x + self._w / 2) * self.image_width), int((self._y + self._h / 2) * self.image_height)

    @property
    def center(self):
        return int(self._x * self.image_width), int(self._y * self.image_height)

if __name__ == '__main__':
    try:
        # Initialiser le robot
        ep_robot = robot.Robot()
        ep_robot.initialize(conn_type="ap")

        # Créer une instance de PersonFollower
        person_follower = PersonFollower(ep_robot)

        # Démarrer le suivi de la personne
        person_follower.follow_person()

    except KeyboardInterrupt:
        print("Interruption clavier. Arrêt du robot.")
    finally:
        # Fermer la connexion au robot
        ep_robot.close()

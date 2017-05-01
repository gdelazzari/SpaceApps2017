# FireDrones
Repository for our NASA Space Apps 2017 project

![](https://github.com/gdelazzari/SpaceApps2017/raw/master/Images/project.png)

## The project
This is our project for the [And YOU can Help Fight Fires!](https://2017.spaceappschallenge.org/challenges/warning-danger-ahead/and-you-can-help-fight-fires/details) challenge in the *Warning! Danger Ahead!* category.

You can check out the main project page on the NASA Space Apps CMS [at this link](https://2017.spaceappschallenge.org/challenges/warning-danger-ahead/and-you-can-help-fight-fires/teams/shc/project).

### General description
Every year there are a lot of wild fires in the world, and they cause a lot of damage (in term of deaths and economic loss). Take a look [here](http://www.nfpa.org/news-and-research/fire-statistics-and-reports/fire-statistics/fires-in-the-us) for example.

We developed a system that takes into consideration both user alerts (made through a mobile app) and signals from an "insight system" (that uses data like [fire risk maps](http://forest.jrc.ec.europa.eu/effis/applications/global-viewer/), weather data, custom sensors data, historical data, etc...) to manage a drone swarm capable of autonomously flying over the interested area and capturing real-time imagery of the fire, which is then processed with a computer vision algorithm to generate a live "fire/smoke size & spreading map".

![](https://github.com/gdelazzari/SpaceApps2017/raw/master/Images/fire_map.jpg)

Once you have this real-time representation of the phenomenon, you can alert the users in the area and show them (through the mobile app) the forecasted fire spread in real time, so they can figure out the best way outs. But, more importantly, the live data can be used by the firefighters to arrive prepared, choosing the best vehicles and tools to extinguish the fire and therefore optimizing their resources (which leads to an economic benefit).

Another bonus feature is that, combining with wind data from weather stations or custom wind sensors deployed near the area, you can predict the direction of the smoke and ash and then alert nearby cities about the danger.

Also, with a system like this, a fire can be detected within tents of minutes instead of hours (satellite live fire data has a latency up to 3 hours - [source](https://earthdata.nasa.gov/earth-observation-data/near-real-time/firms)), thanks to the insight system that, even without a user report, is capable of guessing if something is happening thanks to temperature/thermal sensors that can be deployed in the area. Or, even without this kind of data, the system can plan timed drone patrols based on the calculated risk for that particular moment of year/month/day, all of this taking in consideration the battery life of the drones and leaving enough in case of user reports that require an instant patrol flight.

The system is also expandable and could be used, for example, to report the live status of a volcanic eruption or an avalanche/flood, or maybe to find lost people in the area. The input data for the insight system is also flexible, in the sense that you can, for example, add more sources like Twitter or other social networks to trigger the drones when someone makes a tweet or a post about a fire that has started. You can also use custom sensors based on the scenario: for instance, if you have a forest under an high hill, you can place a thermal camera on the top of the hill to instantly detect any flame.

### Drones and stations
![](https://github.com/gdelazzari/SpaceApps2017/raw/master/Images/drone.png "Drone with base solar station")

The drones will have an auto-pilot system, a GPS unit, a video camera (or optionally a more expensive thermal camera, but it's possible to rely only on standard cameras) and a wireless transmitter to communicate with the rest of the system, sending the video stream and other kinds of data such as their position and current battery life. Whether the drones will send the data directly to the server (and so will have to connect directly to the internet) or the data will go through their respective ground station before being sent to the servers, is a design choice that hasn't still been addressed. However the future arrival of the 5G network will certanly ease the implementation and design of the communication part.

With that said, the drones can be relatively cheap and are charged when they are retired in their ground station, which takes the power from the sun. The ground station also provides infrared-light and other kinds of reference points for the drone to land precisely.

Automatic drone landing on a base recharging station is totally possible as you can see from other people videos on the web: [example 1](https://www.youtube.com/watch?v=XpUdW_U2KJ8), [example 2](https://www.youtube.com/watch?v=061Qhkr7XCE).

### Computer vision analysis of the drone imagery
The live video stream captured by a drone during a fire can quite easly be processed with computer vision or machine learning algorithms such as CNN (Convolutional Neural Networks). For our demo, we trained a really simple feed-forward neural network that classified 8x8 pixels cells of the video frames into one of these categories
+ fire (**red**)
+ smoke (**blue**)
+ nature (**green**, grass/trees/etc: areas still untouched by the fire but flammable)
+ sky

You can find the code used for the demo in the NeuralNetwork directory. For our demo a NN was probably overkill, since we could just have used a simpler classifier (maybe with the average color of the 8x8 cell)... but a neural networks are *cool*, so why not.

Anyway, that was just to prove that a live image analysis to obtain a "fire map" is totally possible.

### Mobile app
![](https://github.com/gdelazzari/SpaceApps2017/raw/master/Images/app.jpg)

The app that everyone will be able to download will be really simple to use, and will show a map that lets you select the location where you spotted the fire and send an alert. You can also view the fire risk map so you know you must be careful in a certain area (a *"Warning, you are in a fire risk area"* alert is also possible). Above you can see a mockup we've made using MIT AppInventor

Besides that, in the event of a nearby fire, as soon as the drones start to report live data of the phenomenon, the analyzed representation of the flames and the smoke is showed in real time so the people can find the best way out and/or prepare themself in case of smoke and ash coming in their direction.

### Sources
+ [US Fire Statistics](http://www.nfpa.org/news-and-research/fire-statistics-and-reports/fire-statistics/fires-in-the-us)
+ [Global Wildfire Information System](http://forest.jrc.ec.europa.eu/effis/applications/global-viewer/)
+ [NASA's Fire Information for Resource Management System](https://earthdata.nasa.gov/earth-observation-data/near-real-time/firms)
+ [(YouTube) Autonomous drone landing on a moving platform](https://www.youtube.com/watch?v=XpUdW_U2KJ8)
+ [(YouTube) Autonomous drone landing on a recharge station](https://www.youtube.com/watch?v=061Qhkr7XCE)

## This repository

Here you will find most of the work we've done to show our concept. The work is divided into the various folders:

+ **Blender** contains all the blender files and textures used to make the 3D animation
+ **Images** contains the images shown in this page
+ **NeuralNetwork** contains the .C programs used to train and generate the video overlay with a Neural Network
+ **SolidEdge** contains all the 3D CAD files for the base station and the drone that were designed using Siemens's Solid Edge

# FireDrones
Repository for our NASA Space Apps 2017 project

![](https://github.com/gdelazzari/SpaceApps2017/raw/master/Images/project.png)

## The team
We are a group of four 19 years old, italian high-school students, with a lot of passion for ICT, electronics, mechanics and all this techy stuff.

We are
+ Giacomo De Lazzari (who is also interested a lot in machine learning)
+ Damiano Tessaro (the electronics guy)
+ Mirco Zenere (our mechanical designer)
+ Cristian Marchetto (our app developer)

## The project
This is our project for the [And YOU can Help Fight Fires!](https://2017.spaceappschallenge.org/challenges/warning-danger-ahead/and-you-can-help-fight-fires/details) challenge in the *Warning! Danger Ahead!* category.

You can check out the main project page on the NASA Space Apps CMS [at this link](https://2017.spaceappschallenge.org/challenges/warning-danger-ahead/and-you-can-help-fight-fires/teams/shc/project).

### General description
Every year there are a lot of wild fires in the world, and they cause a lot of damage (both in term of deaths and economic loss). Take a look [here](http://www.nfpa.org/news-and-research/fire-statistics-and-reports/fire-statistics/fires-in-the-us) for example.

We developed a system that takes into consideration both user alerts (made through a mobile app) and signals from an "insight system" (which uses data like [fire risk maps](http://forest.jrc.ec.europa.eu/effis/applications/global-viewer/) from NASA and other sources, weather data, custom sensors data, historical data, etc...) to manage a drone swarm capable of autonomously flying over the interested area and capture real-time imagery of the fire, which is then processed by a computer vision algorithm to generate a live "fire/smoke size & spreading map".

![](https://github.com/gdelazzari/SpaceApps2017/raw/master/Images/fire_map.jpg)

Once you have this real-time representation of the phenomenon, you can alert the users in the area and show them (through the mobile app) the forecasted fire spread in real time, so they can figure out the best way outs. But, most important, the live data can be used by the firefighters to arrive prepared, choosing the best vehicles and tools to extinguish the fire and therefore optimizing their resources (which leads to an economic benefit).

Another bonus feature is that combining wind data from weather stations or custom wind sensors deployed in the surrounding area (and maybe also on the drone stations themselves), the smoke and ash direction can be predicted and nearby cities can be timely alerted about the danger.

Moreover, a system like this allows a fire to be detected within minutes instead of hours (satellite live fire data has a latency up to 3 hours - [source](https://earthdata.nasa.gov/earth-observation-data/near-real-time/firms)). This is feasible, owing to the insight system which, even without a user report, is capable of guessing if something is happening thanks to temperature/thermal sensors that can be deployed in the area. Or, even without this kind of data, the system can plan timed drone patrols based on the calculated risk for that particular moment of year/month/day, all of this taking into consideration the battery life of the drones and leaving enough in case of user reports that require an instant patrol flight.

The system is also expandable and could be used, for example, to report the live status of a volcanic eruption or an avalanche/flood, or possibly to find people lost in the area. The input data for the insight system is also flexible, in the sense that you can, for example, add more sources like Twitter or other social networks to trigger the drones when someone tweets or posts something about a fire that has started. Futhermore, you can also use custom sensors based on the scenario: for instance, if a forest lies at the foot of an high hill, you can place a thermal camera on the top of the hill to instantly detect any possible flame.

### Drones and stations
![](https://github.com/gdelazzari/SpaceApps2017/raw/master/Images/drone.png "Drone with base solar station")

The drones will be equipped with an auto-pilot system, a GPS unit, a video camera (or optionally a more expensive thermal camera, but it's possible to rely only on standard cameras) and a wireless transmitter to communicate with the rest of the system, sending the video stream and other kinds of data (such as their position and current battery life). Whether the drones will send the data directly to the server (thus having to connect directly to the internet) or the data will go through their respective ground station before being sent to the servers, is a design choice that still has not been addressed. However the future arrival of the 5G network will certanly ease the implementation and design of the communication part.

With that said, the drones can be relatively cheap and are charged when they are retired in their ground station, which gets power from the sun. The ground station also provides infrared-light and other kinds of reference points for the drone to land precisely.

Automatic drone landing on a base recharging station is totally possible as one can see from various videos on the web: [example 1](https://www.youtube.com/watch?v=XpUdW_U2KJ8), [example 2](https://www.youtube.com/watch?v=061Qhkr7XCE).

### Computer vision analysis of the drone imagery
The live video stream captured by a drone during a fire can quite easly be processed with computer vision or machine learning algorithms such as CNN (Convolutional Neural Networks). For our demo, we trained a really simple feed-forward neural network that classified 8x8 pixels cells of the video frames into one of these categories
+ fire (**red**)
+ smoke (**blue**)
+ nature (**green**, grass/trees/etc: areas still untouched by the fire but flammable)
+ sky

Click on the image below to open a [YouTube video](https://www.youtube.com/watch?v=GgVrd8o5Z40) showing a quick demo of our neural network working on a 10 seconds video

[![demo video](https://img.youtube.com/vi/GgVrd8o5Z40/0.jpg)](https://www.youtube.com/watch?v=GgVrd8o5Z40)

You can find the code used for the demo in the NeuralNetwork directory. For our demo a NN was probably overkill, since we could as well have used a simpler classifier (maybe with the average color of the 8x8 cell)... but neural networks are *cool*, ...so why not.

Anyway, that was just to prove that a live image analysis to obtain a "fire map" is totally possible.

### Mobile app
<img align="right" style="margin-left: 16px" src="https://github.com/gdelazzari/SpaceApps2017/raw/master/Images/app.jpg">

The app, which anyone will be able to download, is really simple to use, and will show a map that allows you to select the location where you spotted the fire and send an alert. You can also view the fire risk map so you know you must be careful in a certain area (a *"Warning, you are in a fire risk area"* alert is also possible). On the right you can see a mockup we have made using MIT AppInventor.

In the event of a nearby fire, as soon as the drones start to report live data of the phenomenon, all the users located near the danger are alerted with a notification/sound alarm and the analyzed representation of the flames and the smoke is showed in real time. This will allow everyone to find the best way out and/or prepare themselves in case of smoke and ash coming in their direction.

### Sources
+ [US Fire Statistics](http://www.nfpa.org/news-and-research/fire-statistics-and-reports/fire-statistics/fires-in-the-us)
+ [Global Wildfire Information System](http://forest.jrc.ec.europa.eu/effis/applications/global-viewer/)
+ [NASA's Fire Information for Resource Management System](https://earthdata.nasa.gov/earth-observation-data/near-real-time/firms)
+ [(YouTube) Autonomous drone landing on a moving platform](https://www.youtube.com/watch?v=XpUdW_U2KJ8)
+ [(YouTube) Autonomous drone landing on a recharge station](https://www.youtube.com/watch?v=061Qhkr7XCE)

## This repository

Here you will find most of the work we have done to show our concept. The work has been divided into these folders:

+ **Blender** contains all the blender files and textures used to make the 3D animation
+ **Images** contains the images shown in this page
+ **NeuralNetwork** contains the .C programs used to train and generate the video overlay with a Neural Network
+ **SolidEdge** contains all the 3D CAD files for the base station and the drone that were designed using Siemens's Solid Edge
+ **Android App** contains a file you can import with MIT's AppInventor, which is the app mockup we used for the demo

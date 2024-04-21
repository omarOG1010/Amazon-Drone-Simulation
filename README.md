# Omar Elgohary, Trenton Marple, Shria Patel, Nathan Jorgenson
## Extensions: Drone Battery and Charging Drones and Notifications

# What is the project about (overview of the whole project, not just the hw4)?
## This project is a simulation of a package delivery system. It uses drones as the mode of delivery of packages. Customers are able to view a package scheduling webpage to enter the name of the package and the pickup and drop off the package as well as the search strategy of how the package is being delievered. The user will also be able to subscribe/unsubscribe to get real time updates about the status of the package. In another webpage you will be able to see the map of possible drop offs and pickups as well as robots that will depict the customer, packages and the drone. There are other objects present in the simulation to mimic a real life situation such as a helicopter and a duck. The simulation also has drone recharge stations for when the drone is low on battery and will not make it to the next spot without charging. If the user decides to subscribe, on the left side of the screen there will be a notification bar that will display the updates for the package.  

# How to run the simulation (overview of the whole project, not just the hw4)?
## To run the simulation you have to be in the correct directory and have the correct port system set up. After that you will want to run make clean, make -j and then make run. Once you do so you can log into the  http://127.0.0.1:<port> to display the simulation and then http://127.0.0.1:<port>/schedule.html to display the package scheduling webpage. The user will be able to make personalized choices on the scheduling page and once the pop up "Delivery has been scheduled" is shown, the other webpage should display the feature. 

# What does the simulation do specifically?
## The simulation shows the movement between the robot(customer), drone and the package. The simulation displays the movement of the drone on its journey to deliver the package to the robot. This journey includes if the drone stops at a recharge station to fuel up so it can complete its trip. 

# Drone Battery
## What does it do?
### The Drone Battery is the amount of life a drone. The drone battery is used when it is traveling to different locations for pickup/drop off for packages. There are drone recharge stations throughout the campus that drones will use to feul up so it can successfully complete a trip. 
## Why is it significantly interesting?
### It is significantly interesting because in real life there will not be a drone that is infinitely alive. Drones will have to be recharged in real life based on usage. This makes the simulation display real life events more accurately. 
## How does it add to the existing work? 
## Which design pattern did you choose to implement it and why? 
## Instruction to use this new feature (if the new feature is not user interactable, please mention this as well)
### This feature is not user interactable. It is controlled soley on the usage of the drone. 

# Notifications
## What does it do?
### The Notifications display real time updates of the status of the delivery. 
## Why is it significantly interesting?
### It is significantly interesting because it allows the user to make a choice to subscribe/unsubscribe to notifications which is important in package delivery. This makes the application more favorable to users who may want to use it. 
## How does it add to the existing work? 

## Which design pattern did you choose to implement it and why? 
### We chose to use the Observer pattern.
## Instruction to use this new feature (if the new feature is not user interactable, please mention this as well)
### In the delivery schedule page there is a subscribe and unsubscribe button for the user to use. If the subscribe button is clicked then the notifications will automatically show up in the simulation web page. 

# Sprint retrospective
## We think this project went great, we worked very well together. We stuck by our sprints well and each took on the task we said we would. We were good with sticking to the timeline and cooperating with one another throughout the sprint. One thing that could have been done better during the sprint is we should have had in person meetings and more meetings throughout the sprint. We were able to successfully implement and integrate the two extensions into our existing code. We are happy with what we have presented and have obeyed the SOLID principles for future work. 

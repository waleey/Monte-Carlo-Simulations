import random as rand
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.image import NonUniformImage
import matplotlib.colors as colors
import matplotlib as mpl

#calculation of the direction cosine of the photon after each scattering event according to the mie-HG phase function.  

def getCostheta(g) :
    temp1=rand.random()
    if(g==0):
        return 1-2*temp1
    else:
        temp2= (1+g**2-((1-g**2)/(1-g+2*g*temp1))**2)/(2*g)
        return temp2
      
      

#getting the new direction unit vector of the photon after each scattering. The return type is an array of size 3 which stores the direction cosine alonf x, y, and z axis.

def rotation(mu, g):
    costheta = getCostheta(g)
    phi=2*np.pi*rand.random()
    sintheta=np.sqrt(1-costheta**2)
    sinphi= np.sin(phi)
    cosphi= np.cos(phi)
    
    if(mu[2]==1):
        mu[0]=sintheta*cosphi
        mu[1]=sintheta*sinphi
        mu[2]= costheta
    elif(mu[2]==-1):
        mu[0]=sintheta*cosphi
        mu[1]=-sintheta*sinphi
        mu[2]= -costheta
    else:
        temp_den=np.sqrt(1-mu[2]**2)
        temp1=mu[0]*costheta+(sintheta*(mu[0]*mu[2]*cosphi-mu[1]*sinphi))/(temp_den)
        temp2=mu[1]*costheta+(sintheta*(mu[1]*mu[2]*cosphi+mu[0]*sinphi))/(temp_den)
        temp3=mu[2]*costheta-temp_den*sintheta*cosphi
        
        mu[0:3]=[temp1, temp2, temp3]
        
    return (mu)
  
  
  
  
  
#This is the main monte-carlo simulation.
#this function takes number of photons, absorption-coefficients, scatterin_coefficients, width of the slab, mie parameter g and m as an input.

def mcSimulation(nphotons, sigma_a, sigma_s, d, g, m):
    
    scale=1/nphotons 
    sigma_t=sigma_a+sigma_s 
    Rd=0 
    Tt=0
    xi=np.array([])
    yi=np.array([])
    scatter_count=np.array([])
    
    for n in range(nphotons):
        w=1                #weight of each packet
        p=np.zeros(3)      #Initial Position of the photon
        mu=[0,0,1]
        count=0
        while (w!=0):
            s=- np.log(rand.random())/sigma_t
            if(mu[2]>0):
                DistBound=(d-p[2])/mu[2]
            elif(mu[2]<0):
                DistBound=-p[2]/mu[2]
            if(s>DistBound):
                if(mu[2]>0):
                    Tt=Tt+w
                    xi=np.append(xi, p[0])
                    yi=np.append(yi, p[1])
                elif(mu[2]<0):
                    Rd=Rd+w
                break
            
            p[0]=p[0]+s*mu[0]
            p[1]=p[1]+s*mu[1]
            p[2]=p[2]+s*mu[2]
            count+=1        #every time a photon changes direction its scatter count increases
            dw=sigma_a/sigma_t
            w=w-dw 
            w=np.max([0,w]) #Confusing: this is always going to  be zero? solved== np.max instead of np.min
            if(w<0.001):
                if(rand.random()>1/m):
                    break
                else : 
                    w=w*m
            mu=rotation(mu, g)
        scatter_count=np.append(scatter_count, count)
    return Rd*scale, Tt*scale, xi, yi,scatter_count
            
            
#This function returns a tuple containing Reflectance, Transmittane, x,y coordinate and number of scattering. 

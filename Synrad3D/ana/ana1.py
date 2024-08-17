import os
import glob
import pandas as pd
import matplotlib.pyplot as plt
import math
import numpy as np
from scipy.interpolate import interp1d
from matplotlib.patches import Rectangle, Polygon
from scipy import constants

#---------------------------------------------------------------------------------------#
# Lattice setup
D1_L = 5 	# [m]
B1_L = 5 	# [m]
B1_A = 0.010 	# [rad]
D2_L = 40 	# [m]
B1_R = (B1_L/2.)/math.sin(B1_A/2.)
B1_S = B1_R * B1_A
# Beam pipe aperture
s_section 	= [+0.000, +20.00, +25.00, +30.00, +35.00, +50.00]
ax1_section 	= [+0.025, +0.025, +0.020, +0.020, +0.010, +0.010]
ax2_section 	= [-0.025, -0.025, -0.020, -0.020, -0.010, -0.010]

#--------------------------------
#inDirName = '../sim/output_diff'
#outDirName = './output_diff'
#draw=False # draw data -> True || convert data -> False
#---
#inDirName = '../sim/output_spec'
#outDirName = './output_spec'
#draw=False # draw data -> True || convert data -> False
#---
inDirName = '../sim/output_track'
outDirName = './output_track'
draw=True # draw data -> True || convert data -> False
#--------------------------------

# File names
fTrackName = inDirName+'/photon_track.dat'
fDataName = inDirName+'/synrad3d.dat'
fFigName = outDirName+'/fig.png'
fOutName = outDirName+'/synrad3d_converted.dat'

#---------------------------------------------------------------------------------------#
# Rotate a vector around an axis
def rotate(X, theta, axis='x'):
	#Rotate multidimensional array `X` `theta` degrees around axis `axis`
	c, s = np.cos(theta), np.sin(theta)
	if axis == 'x': 
		return np.dot(X, np.array([
			[1.,  0,  0],
			[0 ,  c, -s],
			[0 ,  s,  c]
		]))
	elif axis == 'y': 
		return np.dot(X, np.array([
			[c,  0,  -s],
			[0,  1,   0],
			[s,  0,   c]
		]))
	elif axis == 'z': 
		return np.dot(X, np.array([
			[c, -s,  0 ],
			[s,  c,  0 ],
			[0,  0,  1.],
		]))
#---------------------------------------------------------------------------------------#
# Convert XYS to XYZ coordinates
def xys_to_xyz(x,y,s,v):
	x_new = x
	y_new = y
	z_new = s
	arc_ang = 0
	if (D1_L < s and s <= D1_L + B1_S): # inside the dipole	
		z_0 = D1_L
		x_0 = x
		arc_len = s - D1_L
		arc_rad = B1_R
		arc_ang = arc_len/arc_rad
		arc_hrd = 2.*(arc_rad*math.sin(arc_ang/2.))
		z_new = z_0 + arc_hrd*math.cos(arc_ang/2.)
		x_new = x_0 - arc_hrd*math.sin(arc_ang/2.)
	elif (D1_L + B1_S < s): # downstream the dipole
		arc_ang = B1_A
		z_0 = D1_L + B1_L*math.cos(B1_A/2.) 
		x_0 = x - B1_L*math.sin(B1_A/2.) 
		drift_s = s - (D1_L + B1_S)
		drift_a = B1_A
		z_new = z_0 + drift_s*math.cos(drift_a)
		x_new = x_0 - drift_s*math.sin(drift_a)
	# Rotate
	v_new = rotate(v,-arc_ang,'y')
	return x_new, y_new, z_new, v_new

#---------------------------------------------------------------------------------------#
# Read photon hit file into dataframe
photon_number_factor = 0
num_photons_generated = 0
e_filter_min = 0
with open(fDataName, 'r') as f:
	# Loop over lines in the file
	for line in f:
		# Skip header lines which start with '#'
		if line.startswith('#'):
			# Split the line by spaces, make words
			line = line.split()
			# Loop over word in the line
			for word_i in range(len(line)):
				if line[word_i] == 'photon_number_factor':
					photon_number_factor = float(line[word_i+2])
				elif line[word_i] == 'num_photons_generated':
					num_photons_generated = float(line[word_i+2])
				elif line[word_i] == 'e_filter_min':
					e_filter_min = float(line[word_i+2])
			continue

print(f"photon_number_factor = {photon_number_factor}")
print(f"num_photons_generated = {num_photons_generated}")

gamma=3.5225121E+04 # From Bmad/Tao
t_s = (B1_A*B1_L/(2.*math.sin(B1_A/2.)))/constants.speed_of_light;
nPh = t_s*(1./137.)*gamma*constants.speed_of_light*5./((B1_L/(2.*math.sin(B1_A/2.)))*2.*math.sqrt(3.))

print(f"photon_number_factor * num_photons_generated = {photon_number_factor*num_photons_generated:.3f} [ph/e] <> calc. = {nPh:.3f} [ph/e]")
print(f"e_filter_min = {e_filter_min} [eV]")
# Read data
data_hits = pd.read_csv(	
	fDataName,
	sep='\s+',
	comment='#',
	names=[	"phIndx", 	# Photon index number
		"numHit", 	# The number of times the photon has struck the vacuum 
				# chamber wall including the final hit 
		"ene",		# The photon energy (in eV)
		"ini_x", "ini_vx", "ini_y", "ini_vy", "ini_s", "ini_vs",	# Initial photon position
		"brIndxCrt",	# Index of the lattice branch where the photon was created
		"fin_x", "fin_vx", "fin_y", "fin_vy", "fin_s", "fin_vs",	# Final photon position
		"sinGrAngl",	# sin(graze_angle). 0 = Grazing incidence, 1 = perpendicular incidence
		"pathLen",	# Photon travel length
		"deltaS",	# Photon longitudinal travel length - beam travel length in the same time period
		"brIndxAbs",	# Index of the lattice branch where the photon is absorbed
		"eleIndx", 	# Lattice element index where photon is absorbed
		"eleType",	# Lattice element type (Eg: quadrupole, etc.) where photon is absorbed
		"subChmbrName"	# Sub-chamber name where photon is absorbed
	]
)	
#---------------------------------------------------------------------------------------#
# Convert coordinates from XYS to XYZ and close without drawing
if not draw:
	# Open the output file to write
	f = open(fOutName, "w")
	# Write a header
	f.write("#index \t ")
	f.write("x_ini \t y_ini \t z_ini \t vx_ini \t vy_ini \t vz_ini \t ")
	f.write("x_fin \t y_fin \t z_fin \t vx_fin \t vy_fin \t vz_fin \t ")
	f.write("ene \t weight\n")
	for index, row in data_hits.iterrows():
		# Convert coordinates from XYS to XYZ
		x_ini,y_ini,z_ini,v_ini = xys_to_xyz(row['ini_x'],row['ini_y'],row['ini_s'],[row['ini_vx'],row['ini_vy'],row['ini_vs']])
		x_fin,y_fin,z_fin,v_fin = xys_to_xyz(row['fin_x'],row['fin_y'],row['fin_s'],[row['fin_vx'],row['fin_vy'],row['fin_vs']])
		f.write(f"{index} \t ")
		f.write(f"{x_ini:.6f} \t {y_ini:.6f} \t {z_ini:.6f} \t {v_ini[0]:.6f} \t {v_ini[1]:.6f} \t {v_ini[2]:.6f} \t ")
		f.write(f"{x_fin:.6f} \t {y_fin:.6f} \t {z_fin:.6f} \t {v_fin[0]:.6f} \t {v_fin[1]:.6f} \t {v_fin[2]:.6f} \t ")
		f.write(f"{row['ene']:.6f} \t {photon_number_factor:.6e}\n")
	# Close the output file
	f.close()
	print('Output file name: ',fOutName)
	# Stop program
	exit()	

#---------------------------------------------------------------------------------------#
# Read photon track file into dataframe
data_trks = pd.read_csv(	
	fTrackName,
	sep='\s+',
	names=[	"phIndx", 		# Photon index
		"genIndx", 		# Generated photon index
		"x","y","s", 		# Coordinates of photon
		"ix_branch", 		# Index of lattice branch photon is in
		"vx", "vy", "vs" 	# Velocity of the photon
	]
)
#---------------------------------------------------------------------------------------#
# Create the scatter plot
fig, ax = plt.subplots(2, 1,figsize=(8,8))
# set the spacing between subplots
plt.subplots_adjust(left=0.18,
                    bottom=0.1, 
                    right=0.9, 
                    top=0.9, 
                    wspace=0.4, 
                    hspace=0.6)
#---------------------------------------------------------------------------------------#
# Draw the orbit in the XYZ system
z_orbit = []
x_orbit = []
for s_orbit_step in np.arange(s_section[0],s_section[-1]+0.1,0.1):
	x,y,z,v = xys_to_xyz(0,0,s_orbit_step,[0,0,0])
	z_orbit.append(z)
	x_orbit.append(x)
ax[1].plot(z_orbit,x_orbit,linestyle='-.',label='orbit',linewidth=1,alpha=0.5,color='black')
#---------------------------------------------------------------------------------------#
# Draw the orbit in the XYS system
ax[0].plot([s_section[0],s_section[-1]],[0,0],linestyle='-.',label='orbit',linewidth=1,alpha=0.5,color='black')
#---------------------------------------------------------------------------------------#
# Draw a dipole
# XZ
z_dipole = []
x_dipole = []
z_dipole_center = D1_L
x_dipole_center = -B1_R
r_dipole = B1_R
for a_dipole_step in np.arange(0,B1_A,0.0001):
	z_dipole.append(z_dipole_center+r_dipole*math.sin(a_dipole_step))
	x_dipole.append(x_dipole_center+(r_dipole+ax1_section[0])*math.cos(a_dipole_step))
for a_dipole_step in np.arange(B1_A,0,-0.0001):
	z_dipole.append(z_dipole_center+r_dipole*math.sin(a_dipole_step))
	x_dipole.append(x_dipole_center+(r_dipole+ax2_section[0])*math.cos(a_dipole_step))
ax[1].add_patch(Polygon(np.vstack((z_dipole,x_dipole)).T,facecolor='red',alpha=0.2,label='dipole'))
# XS
ax[0].add_patch(Rectangle((D1_L,ax2_section[0]), B1_L, ax1_section[0]-ax2_section[0],facecolor='red',alpha=0.2,label='dipole'))
#---------------------------------------------------------------------------------------#
# Draw beam pipe aperture
ax[0].plot(s_section,ax1_section,linestyle='--',label='aperture',linewidth=2,alpha=1.0,color='black')
ax[0].plot(s_section,ax2_section,linestyle='--',                 linewidth=2,alpha=1.0,color='black')

z_section_new = []
ax1_section_new = []
ax2_section_new = []
interp_func1 = interp1d(s_section,ax1_section)
interp_func2 = interp1d(s_section,ax2_section)

for s in np.arange(0,s_section[-1]+0.1,0.1):
	ax1 = interp_func1(s)
	ax2 = interp_func2(s)
	axx1,yy,z,v = xys_to_xyz(ax1,0,s,[0,0,0])
	axx2,yy,z,v = xys_to_xyz(ax2,0,s,[0,0,0])
	ax1_section_new.append(axx1)
	ax2_section_new.append(axx2)
	z_section_new.append(z)

ax[1].plot(z_section_new,ax1_section_new,linestyle='--',label='aperture',linewidth=2,alpha=1.0,color='black')
ax[1].plot(z_section_new,ax2_section_new,linestyle='--',                 linewidth=2,alpha=1.0,color='black')
#---------------------------------------------------------------------------------------#
# Get indices of photons
photon_indexes = data_trks['phIndx'].unique()

# Loop over photons
first0=True
first1=True
for index in photon_indexes:
	photon_data = data_trks[data_trks['phIndx'] == index]
	# Draw the track in the XYS system
	if first0:
		ax[0].plot(photon_data['s'],photon_data['x'],linestyle='-',linewidth=1,alpha=0.5,color='green',label='photon')
	else:
		ax[0].plot(photon_data['s'],photon_data['x'],linestyle='-',linewidth=1,alpha=0.5,color='green')
	# Draw the track in the XYZ system
	x_new = []
	y_new = []
	z_new = []
	# Loop over the given track coordinates
	for x,y,s,vx,vy,vs in zip(	photon_data['x'],photon_data['y'],photon_data['s'],
					photon_data['vx'],photon_data['vy'],photon_data['vs']):
		xx,yy,zz,vv = xys_to_xyz(x,y,s,[vx,vy,vs])
		x_new.append(xx)
		y_new.append(yy)
		z_new.append(zz)
	if first1:
		ax[1].plot(z_new,x_new,linestyle='-',linewidth=1,alpha=0.5,color='green',label='photon')
	else:
		ax[1].plot(z_new,x_new,linestyle='-',linewidth=1,alpha=0.5,color='green')

	photon_data = data_hits[data_hits['phIndx'] == index]
	# Draw photon initial/final coordinates in the XYS system
	if first0:
		ax[0].plot(photon_data['ini_s'],photon_data['ini_x'],marker='o',markersize=4,alpha=0.5,color='blue',label='initial pos.')
		ax[0].plot(photon_data['fin_s'],photon_data['fin_x'],marker='o',markersize=4,alpha=0.5,color='red',label='final pos.')
	else:
		ax[0].plot(photon_data['ini_s'],photon_data['ini_x'],marker='o',markersize=4,alpha=0.5,color='blue')
		ax[0].plot(photon_data['fin_s'],photon_data['fin_x'],marker='o',markersize=4,alpha=0.5,color='red')
	# Draw the track in the XYZ system
	x_ini_new = []
	y_ini_new = []
	z_ini_new = []
	x_fin_new = []
	y_fin_new = []
	z_fin_new = []
	# Loop over the given track coordinates
	for x_ini,y_ini,s_ini,x_fin,y_fin,s_fin,vx_ini,vy_ini,vs_ini,vx_fin,vy_fin,vs_fin in zip(	
			photon_data['ini_x'],photon_data['ini_y'],photon_data['ini_s'],
			photon_data['fin_x'],photon_data['fin_y'],photon_data['fin_s'],
			photon_data['ini_vx'],photon_data['ini_vy'],photon_data['ini_vs'],
			photon_data['fin_vx'],photon_data['fin_vy'],photon_data['fin_vs']
		):
		xx,yy,zz,vv = xys_to_xyz(x_ini,y_ini,s_ini,[vx_ini,vy_ini,vs_ini])
		x_ini_new.append(xx)
		y_ini_new.append(yy)
		z_ini_new.append(zz)
		xx,yy,zz,vv = xys_to_xyz(x_fin,y_fin,s_fin,[vx_fin,vy_fin,vs_fin])
		x_fin_new.append(xx)
		y_fin_new.append(yy)
		z_fin_new.append(zz)

	if first1:
		ax[1].plot(z_ini_new,x_ini_new,marker='o',markersize=4,alpha=0.5,color='blue',label='initial pos.')
		ax[1].plot(z_fin_new,x_fin_new,marker='o',markersize=4,alpha=0.5,color='red',label='final pos.')
	else:
		ax[1].plot(z_ini_new,x_ini_new,marker='o',markersize=4,alpha=0.5,color='blue')
		ax[1].plot(z_fin_new,x_fin_new,marker='o',markersize=4,alpha=0.5,color='red')
	
	# Set boolean keys to avoid duplication of labels in the legend
	first0 = False
	first1 = False
#---------------------------------------------------------------------------------------#
# Drawing settings

# Axis title
ax[0].set_xlabel('S [m]', fontsize = 20)
ax[0].set_ylabel('X [m]', fontsize = 20)
ax[1].set_xlabel(r'$\rm Z_{glob.}$ [m]', fontsize = 20)
ax[1].set_ylabel(r'$\rm X_{glob.}$ [m]', fontsize = 20)

# Axis tick size
ax[0].tick_params(axis='both', which='major', labelsize=20)
ax[1].tick_params(axis='both', which='major', labelsize=20)

# Add title
ax[0].set_title('SR tracks in the X-S beam coordinate system', fontsize = 20)
ax[1].set_title('SR tracks in the X-Z global coordinate system', fontsize = 20)

# Add a grid
ax[0].grid(True, linestyle='--', alpha=0.7)
ax[1].grid(True, linestyle='--', alpha=0.7)
# Set ranges
ax[0].set_xlim([-5, 55])
ax[1].set_xlim([-5, 55])
ax[1].set_ylim([-0.5, 0.3])

# Draw legend
ax[1].legend(loc=1, prop={'size': 12})

fig.savefig(fFigName)	# save the figure to file

# Draw all
plt.show()

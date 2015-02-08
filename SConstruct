import os

#--- QT VERSION ---
qtver = ['qt5', 'QT5DIR', '/home/frank/Qt5.4.0/5.4/gcc_64']

# Create base environment
baseEnv = Environment()
#...further customization of base env

# Clone Qt environment
qtEnv = baseEnv.Clone()

# Set QT#DIR and PKG_CONFIG_PATH
qtEnv['ENV']['PKG_CONFIG_PATH'] = os.path.join(qtver[2], 'lib/pkgconfig')
qtEnv[qtver[1]] = qtver[2]

# Add qt5 tool
qtEnv.Tool(qtver[0])

#...further customization of qt env
qtEnv.Append( CPPFLAGS = [
    '-fPIC'
    ,'-std=c++0x'
    ])

# Export environments
Export('baseEnv qtEnv')

# Your other stuff...

# ...including the call to your SConscripts
SConscript('SConscript')


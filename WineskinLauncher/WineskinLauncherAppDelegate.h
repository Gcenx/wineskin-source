//
//  WineskinAppDelegate.h
//  Wineskin
//
//  Copyright 2014 by The Wineskin Project and Urge Software LLC All rights reserved.
//  Licensed for use under the LGPL <http://www.gnu.org/licenses/lgpl-2.1.txt>
//

#import <Cocoa/Cocoa.h>
#import "WineStart.h"
#import "NSPortManager.h"

@interface WineskinLauncherAppDelegate : NSObject <NSApplicationDelegate>
{
    NSPortManager* portManager;
    
    BOOL primaryRun;
    BOOL wrapperRunning;
	IBOutlet NSWindow *window;
	IBOutlet NSProgressIndicator *waitWheel;
    NSFileManager *fm;
    NSMutableArray *globalFilesToOpen;
    NSString *contentsFold;                         //Contents folder in the wrapper
	NSString *frameworksFold;                       //Frameworks folder in the wrapper
	NSString *appNameWithPath;                      //full path to and including the app name
    NSString *appName;                              //name of our app/wrapper
	NSString *lockfile;                             //lockfile being used to know if the app is already in use
    NSString *tmpFolder;                            //where tmp files can be made and used to be specific to just this wrapper
    NSString *tmpwineFolder;                        //wine makes its own tmp & wineserver uses it for each wine process
	NSString *winePrefix;                           //the $WINEPREFIX
    NSString *pathToWineBinFolder;
	NSMutableString *theDisplayNumber;              //the Display Number to use
    NSString *wineLogFile;                          //location of wine log file
    NSString *wineTempLogFile;                      //location of wine temp log file
    NSString *x11LogFile;                           //location of x11 log file
	BOOL fullScreenOption;                          //wether running fullscreen or rootless (RandR is rootless)
	BOOL useGamma;                                  //wether or not gamma correction will be checked for
	BOOL useXQuartz;                                //YES if using XQuartz over Mac Driver
	NSMutableString *gammaCorrection;               //added in gamma correction
	NSMutableString *fullScreenResolutionBitDepth;	//fullscreen bit depth for X server
	NSString *currentResolution;                    //the resolution that was running when the wrapper was started
	NSString *wrapperBundlePID;                     //PID of running wrapper bundle
	NSMutableString *xQuartzX11BinPID;              //PID of running XQuartz X11.bin (only needed for Override->Fullscreen)
	NSString *xQuartzBundlePID;                     //PID of running XQuartz bundle (only needed for Override->Fullscreen)
	BOOL debugEnabled;                              //set if debug mode is being run, to make logs
	BOOL isIce;                                     //YES if ICE engine being used
    BOOL removeX11TraceFromLog;                     //YES if Wineskin added the X11 trace to winedebug to remove them from the output log
	NSString *dyldFallBackLibraryPath;              //the path for DYLD_FALLBACK_LIBRARY_PATH
    NSString *wineExecutable;                       //the wine executable that will be used for all launches
    NSString *fontFix;                              //force freetype into using rendering mode from pre 2.7
    BOOL useMacDriver;                              //YES if using Mac Driver over X11
    NSString *wineServerName;                       //the name of the Wineserver we'll be launching
    NSString *wineName;                             //the name of the Wine process we'll be launching
    NSString *wine64Name;                           //the name of the Wine64 process we'll be launching
    NSString *wineStagingName;                      //the name of the Wine-preloader process we'll be launching
    NSString *wine32on64Name;                       //the name of the Wine32on64-preloader process we'll be launching
    NSString *wineStaging64Name;                    //the name of the Wine64-preloader process we'll be launching
	int bundleRandomInt1;
    int bundleRandomInt2;
    
}
// if Fn or Alt held on run
- (void) doSpecialStartup;

//run system command with output returned
- (NSString *)systemCommand:(NSString *)command;

//the main running of the program...
- (void)mainRun:(NSArray*)filesToOpen;

//Any time its re-ran after its already running, for like opening extra files or Custom EXEs
- (void)secondaryRun:(NSArray*)filesToOpen;

//used to change the gamma setting since Xquartz cannot yet
- (void)setGamma:(NSString *)inputValue;

//used to change the global screen resolution for overriding randr
- (void)setResolution:(NSString *)reso;

//returns the current screen resolution
- (NSString *)getScreenResolution;

//Makes an Array with a list of PIDs that match the process name
- (NSArray *)makePIDArray:(NSString *)processToLookFor;

//returns PID of new process (after it appears)
- (NSString *)getNewPid:(NSString *)processToLookFor from:(NSArray *)firstPIDlist confirm:(bool)confirm_pid;

//sets the drive_c/user/Wineskin folder correctly for a run
- (void)setUserFolders:(BOOL)doSymlinks;

//Makes sure the current user owns the winepeefix, or Wine will not run
- (void)fixWinePrefixForCurrentUser;

//Tries to get the GPU info and enter it in the Wine Registry, use before starting Wine
- (void)tryToUseGPUInfo;

//remove GPU info from Registry
- (void)removeGPUInfo;

//returns the correct line needed for startXQuartz to get the right quartz-wm started
- (NSString *)setWindowManager;

//checks if Mac is set in Wine
- (BOOL)checkToUseMacDriver;

//check if XQuartz is installed
-(BOOL)isXQuartzInstalled;

//starts up XQuartz
- (void)startXQuartz;

//bring the app to the front most
- (void)bringToFront:(NSString *)thePid;

//installs ICE files
- (void)installEngine;

//Changes VD Desktop user.reg entries to a given virtual desktop
- (void)setToVirtualDesktop:(NSString *)resolution;

//Changes VD Desktop user.reg entires to not have a virtual desktop
- (void)setToNoVirtualDesktop;

//reads a file and passes back contents as an array of strings
- (NSArray *)readFileToStringArray:(NSString *)theFile;

//writes an array to a normal text file, each entry on a line.
- (void)writeStringArray:(NSArray *)theArray toFile:(NSString *)theFile;

//returns true if running PID has the specified name
- (BOOL)isPID:(NSString *)pid named:(NSString *)name;

//returns true if Wineserver for this wrapper is running
- (BOOL)isWineserverRunning;

//fix wine and wineserver names in engines to be unique for launch
- (void)fixWineExecutableNames;

//fix wine and wineserver names
- (void)fixWine32ExecutableNames;

//fix wine, wine64 and wineserver names
- (void)fixWine64ExecutableNames;

//fix wine-preloader and wineserver names
- (void)fixWineStagingExecutableNames;

//fix wine-preloader, wine64-preloader and wineserver names
- (void)fixWineStaging64ExecutableNames;

//fix wine-preloader, wine32on64-preloader and wineserver names
- (void)fixWine32on64ExecutableNames;

//fix wine-preloader, wine32on64-preloader, wine64-preloader and wineserver names
- (void)fixWine32on64_64BitExecutableNames;

//fix wine64 and wineserver names
- (void)fixWine64_No_Wine32_ExecutableNames;

//fix wine64-prealoder
-(void)fixWinestaging64_No_Wine32_ExecutableNames;

//fix wine32on64-preloader & wine64 without wine
-(void)fixWine32on64_64Bit_No_Wine32_ExecutableNames;

//fix wine32on64-preloader without wine & wine64
-(void)fixWine32on64_No_Wine32_ExecutableNames;

//start wine
- (void)startWine:(WineStart *)wineStart;

//background monitoring while Wine is running
- (void)sleepAndMonitor;

//run when shutting down
- (void)cleanUpAndShutDown;

@end

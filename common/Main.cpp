#include "../../../juce.h"
#include "GameThread.h"

class GameContentComponent    : public Component, public ButtonListener, public ChangeListener
{
	GameThread* game;
	TextButton startGameButton;
	Label seed;
	Label lines;
	Image* blockPreview;
public:
	GameContentComponent() : startGameButton(T("Start New Game")), seed(T("Random seed"), T("0")), lines(T("Lines removed"), T("0"))
	{
		setWantsKeyboardFocus(true);
		addAndMakeVisible(&startGameButton);
		addAndMakeVisible(&seed);
		addAndMakeVisible(&lines);
		startGameButton.setBounds(330,0,70,30);
		startGameButton.addButtonListener(this);
		seed.setBounds(330,40,70,30);
		seed.setEditable(true);
		seed.setText(String(Time::getApproximateMillisecondCounter()),true);
		lines.setBounds(330,80,70,30);
		game = new GameThread(310,605,this);
		game->addChangeListener(this);
		game->getBlockManager()->addChangeListener(this);
		blockPreview = game->getBlockManager()->getBlockPreviewImage();
	}

	~GameContentComponent()
	{
		game->stopThread(1000);
		delete game;
	}

	void buttonClicked(Button* button)
	{
		if(button == &startGameButton)
		{
			int randSeed = seed.getText().getIntValue();
			game->setSeed(randSeed);
			startGame();
			seed.setEnabled(false);
		}
	}

	void changeListenerCallback(void* objectThatHasChanged)
	{
		if(objectThatHasChanged == game->getBlockManager())
		{
			repaint();
		}
		else
		{
			int n = (int)objectThatHasChanged;
			lines.setText(String(n) + T(" lines"),false);
		}
	}

	void startGame()
	{
		game->startThread();
	}

	bool keyPressed(const KeyPress& key)
	{
		int n = key.getKeyCode();
		if(n == KeyPress::leftKey)
		{
			game->moveBlockLeft();
		}
		else if(n == KeyPress::rightKey)
		{
			game->moveBlockRight();
		}
		else if(n == KeyPress::upKey)
		{
			game->rotateBlockRight();
		}
		else if(n == KeyPress::downKey)
		{
			game->moveBlockDown();
		}
		return true;
	}

	void paint (Graphics& g)
	{
		// clear the background with solid white
		g.fillAll (Colours::white);

			game->lockCanvas();
			Image* canvas = game->getCanvas();
			if(canvas != 0)
			{
				g.drawImageAt(canvas,0,0);
			}
			g.drawImageAt(blockPreview, 330, 100);
			game->unlockCanvas();
	}
};

//==============================================================================
/** This is the top-level window that we'll pop up. Inside it, we'll create and
show a HelloWorldContentComponent component.
*/
class GameWindow  : public DocumentWindow
{
public:
	GameWindow()
		: DocumentWindow (T("Game"),
		Colours::lightgrey, 
		DocumentWindow::allButtons, 
		true)
	{
		GameContentComponent* comp = new GameContentComponent();
		setContentComponent (comp);
		setVisible (true);
		// centre the window on the desktop with this size
		centreWithSize (400, 633);
	}

	~GameWindow()
	{
		// (the content component will be deleted automatically, so no need to do it here)
	}

	void closeButtonPressed()
	{
		// When the user presses the close button, we'll tell the app to quit. This 
		// window will be deleted by the app object as it closes down.
		JUCEApplication::quit();
	}
};


//==============================================================================
/** This is the application object that is started up when Juce starts. It handles
the initialisation and shutdown of the whole application.
*/
class JUCEGameApplication : public JUCEApplication
{
	GameWindow* gameWindow;
public:
	JUCEGameApplication()
		: gameWindow (0)
	{
	}

	~JUCEGameApplication()
	{
	}

	void initialise (const String& commandLine)
	{
		gameWindow = new GameWindow();
	}

	void shutdown()
	{
		if (gameWindow != 0)
			delete gameWindow;
	}

	const String getApplicationName()
	{
		return T("Game");
	}

	const String getApplicationVersion()
	{
		return T("1.0");
	}

	bool moreThanOneInstanceAllowed()
	{
		return true;
	}

	void anotherInstanceStarted (const String& commandLine)
	{
	}
};


//==============================================================================
// This macro creates the application's main() function..
START_JUCE_APPLICATION (JUCEGameApplication)

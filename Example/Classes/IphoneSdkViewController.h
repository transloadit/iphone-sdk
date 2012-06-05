#import <QuartzCore/CALayer.h>
#import "TransloaditRequest.h"

@interface IphoneSdkViewController : UIViewController <UIImagePickerControllerDelegate, UINavigationControllerDelegate> 
{
	TransloaditRequest *transload;
	
	IBOutlet UIButton *button;
	IBOutlet UIImageView *thumb;
	IBOutlet UIProgressView *progressBar;
	IBOutlet UILabel *status;
	IBOutlet UIActivityIndicatorView *spinner;
}

@property(nonatomic, retain) IBOutlet UIButton *button;
@property(nonatomic, retain) IBOutlet UIImageView *thumb;
@property(nonatomic, retain) IBOutlet UIProgressView *progressBar;
@property(nonatomic, retain) IBOutlet UILabel *status;
@property(nonatomic, retain) IBOutlet UIActivityIndicatorView *spinner;

- (IBAction)buttonTouch;

@end
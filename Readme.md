This SDK is deprecated. Please checkout our [new iOS SDK](https://github.com/transloadit/ios-sdk).

# Transloadit iPhone SDK

The transloadit iPhone SDK contains the `TransloaditRequest` class and related dependencies. In addition, an example iPhone project is provided to help get you started.

<a href="https://github.com/transloadit/iphone-sdk/raw/master/Screenshots/device/1.png">
<img src="https://github.com/transloadit/iphone-sdk/raw/master/Screenshots/device/1.png" height="500">
</a>
<a href="https://github.com/transloadit/iphone-sdk/raw/master/Screenshots/device/2.png">
<img src="https://github.com/transloadit/iphone-sdk/raw/master/Screenshots/device/2.png" height="500">
</a>

## Getting started

Within the `Example` directory, open the `TransloaditIphoneSdk.xcodeproj` in XCode 4+. The first thing you should do is edit the `Config.m` file that comes with the project. You will need a [transloadit](http://transloadit.com/) account, as well
as a [template id](http://transloadit.com/docs/templates).

Once you have set this up, you can start the example app and test some file uploads.

## Using Transloadit in your own app

In order to use the SDK in your own app, simply drag the `TransloaditSDK` directory into your XCode project.

The `TransloaditRequest` class depends on two additional libraries that are included:

* [JSONKit](https://github.com/johnezang/JSONKit) (Dual Licensed BSD & Apache 2.0)
* [ASIHttpRequest](https://github.com/pokeb/asi-http-request/) (BSD License)

## Example - UIImagePickerController

Assuming you have a `UIImagePickerController` callback, you can upload the selected
file like this:

```objective-c
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    TransloaditRequest *transload = [[TransloaditRequest alloc] initWithCredentials:@"your-key" secret:@"your-secret"];
    [transload setTemplateId:@"your-template-id"];
    [transload addPickedFile:info];
    [transload setNumberOfTimesToRetryOnTimeout:5];
    [transload setDelegate:self];
    [transload setUploadProgressDelegate:self];
    [transload startAsynchronous];
}

- (void)setProgress:(float)currentProgress
{
    NSLog(@"upload progress: %f", currentProgress);
}

- (void)requestFinished:(TransloaditRequest *)transload
{
    NSString *assemblyId = [[transload response] objectForKey:@"assembly_id"];
    NSLog(@"assembly id: %@", assemblyId);
    [transload release];
}
```

If you need to pass dynamic `params` instead of just a template id, you can
tweak the example from above like this:

```objective-c
// [transload setTemplateId:@"your-template-id"];
NSMutableDictionary *steps = [[NSMutableDictionary alloc] init];
NSMutableDictionary *resizeStep = [[NSMutableDictionary alloc] init];
[resizeStep setObject:@"/image/resize" forKey:@"robot"];
[resizeStep setObject:[NSNumber numberWithInt:100] forKey:@"width"];
[resizeStep setObject:[NSNumber numberWithInt:100] forKey:@"height"];
[steps setObject:resizeStep forKey:@"resize"];
[[transload params] setObject:steps forKey:@"steps"];
```
## Example - Audio from file path

```objective-c
- (void)transloadAudioFile
{
    NSString *myPath = @"/someLocalFile.wav";
    
    TransloaditRequest *transload = [[TransloaditRequest alloc] initWithCredentials:@"your-key" secret:@"your-secret"];
    [transload setTemplateId:@"your-template-id"];
    [transload addRawFile:myPath withFileName:@"myfile.wav" addContentType:@"audio/wav"];
    [transload setNumberOfTimesToRetryOnTimeout:5];
    [transload startAsynchronous];
}
```

## Example - Image from NSData

```objective-c
- (void)transloadImageData
{
    NSData *myData = UIImagePNGRepresentation([UIImage imageNamed:@"myImageFile.png"]);

    TransloaditRequest *transload = [[TransloaditRequest alloc] initWithCredentials:@"your-key" secret:@"your-secret"];
    [transload setTemplateId:@"your-template-id"];
    [transload addRawData:myData withFileName:@"myfile.png" addContentType:@"image/png"];
    [transload setNumberOfTimesToRetryOnTimeout:5];
    [transload startAsynchronous];
}
```

## TransloaditRequest API

#### @property(nonatomic, retain) NSMutableDictionary \*params;

The `params` field with the instructions that will be send to transloadit.

#### @property(nonatomic, retain) NSDictionary \*response;

The parsed [response](http://transloadit.com/docs/assemblies#response-format) from transloadit.

#### - (id)initWithCredentials:(NSString \*)key secret:(NSString \*)secret;

Initializes a transloadit request with the given `key` and `secret`.

#### - (void)addRawFile:(NSString *)path withFileName:(NSString *)filename addContentType:(NSString *)type;

Takes a local file from the specified path and prepares it for uploading. This can be a video, image or audio file.

#### - (void)addRawData:(NSData *)data withFileName:(NSString *)filename addContentType:(NSString *)type;

Takes the data from as `NSData` object and prepares it for uploading. The can be a video, image or audio file.

#### - (void)addPickedFile:(NSDictionary \*)info;

Takes a picked file and prepares it for uploading. This can either be a video or an image.

#### - (void)addPickedFile:(NSDictionary \*)info forField:(NSString \*)field;

Same as the above, but you can specify the form field name to be used for this
upload.

#### - (void)setTemplateId:(NSString \*)templateId;

Sets the `TransloaditRequest.params.template_id` property.

#### - (bool)hadError;

Returns `true` if transloadit returned an error code.

## License

The Transloadit iPhone SDK is licensed under the MIT license. The dependencies
have their own licenses.

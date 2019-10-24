
import Cocoa
import Metal
import MetalKit
import Darwin

import mlx_image


class WinEvent: NSWindow
{
  var eventFuncts = [UnsafeMutableRawPointer?]()
  var eventParams = [UnsafeMutableRawPointer]()

  var keyrepeat = 1
  var keyflag:UInt32 = 0

  var size_y:Int

  init(frame rect:CGRect)
  {
    for _ in 0...31
    {
      eventFuncts.append(Optional.none)
      eventParams.append(UnsafeMutableRawPointer(&keyrepeat)) /// dummy address here, null not needed
    }

    let wsm = NSWindow.StyleMask(rawValue: NSWindow.StyleMask.titled.rawValue|NSWindow.StyleMask.closable.rawValue|NSWindow.StyleMask.miniaturizable.rawValue)
    let bck = NSWindow.BackingStoreType.buffered
    size_y = Int(rect.size.height)
    super.init(contentRect: rect, styleMask: wsm, backing: bck, defer: false)
  }

  public func setKeyRepeat(_ mode:Int)
  {
	keyrepeat = mode;
  }


  func addHook(index idx:Int, fct fptr:UnsafeMutableRawPointer?, param pptr:UnsafeMutableRawPointer)
  {
	eventFuncts[idx] = fptr;
	eventParams[idx] = pptr;
	if (idx == 6 || idx == 32)
	{
		if (fptr != nil) ///  == nullptr)
		   { self.acceptsMouseMovedEvents = false }
		else { self.acceptsMouseMovedEvents = true }
	}
  }


  override func keyDown(with event: NSEvent)
  {
	/// print("got keydown with code: \(event.keyCode) ")
	if (event.isARepeat && keyrepeat == 0)
	 { return }
	if (eventFuncts[2] != nil)
	{
	  _ = unsafeBitCast(eventFuncts[2],to:(@convention(c)(Int32, UnsafeRawPointer)->Int32).self)(Int32(event.keyCode), eventParams[2])
	}
  }


  override func keyUp(with event: NSEvent)
  {
	/// print("got keyup with code: \(event.keyCode) and calling key hook")
	if (event.isARepeat && keyrepeat == 0)
	 { return }
	if (eventFuncts[3] != nil)
	{
	  _ = unsafeBitCast(eventFuncts[3],to:(@convention(c)(Int32, UnsafeRawPointer)->Int32).self)(Int32(event.keyCode), eventParams[3])
	}
  }


  func get_mouse_button(with ev:NSEvent) -> Int
  {
	switch (ev.type) {
  	       case NSEvent.EventType.leftMouseDown,
	       	    NSEvent.EventType.leftMouseUp,
	       	    NSEvent.EventType.leftMouseDragged:
	           return 1;
	       case NSEvent.EventType.rightMouseDown,
	       	    NSEvent.EventType.rightMouseUp,
	            NSEvent.EventType.rightMouseDragged:
	           return 2;
	       case NSEvent.EventType.otherMouseDown,
	            NSEvent.EventType.otherMouseUp,
	            NSEvent.EventType.otherMouseDragged:
	           return 3;
	       default:
	           return 0;
        }
  }



  func mouse(with event: NSEvent, index idx:Int, type t:Int)
  {
	var thepoint:NSPoint
	var button:Int

	thepoint = event.locationInWindow
	button = get_mouse_button(with:event)
	/// button = event.buttonNumber
	/// print(" mouse down button \(event.buttonNumber) at location \(thepoint.x) x \(thepoint.y)")
	if (eventFuncts[idx] != nil)
	{
	  if (t == 0)
	   { _ = unsafeBitCast(eventFuncts[idx],to:(@convention(c)(Int32, Int32, Int32, UnsafeRawPointer)->Int32).self)(Int32(button), Int32(thepoint.x), Int32(size_y-1-Int(thepoint.y)), eventParams[idx]) }
	  if (t == 1)
	   { _ = unsafeBitCast(eventFuncts[idx],to:(@convention(c)(Int32, Int32, UnsafeRawPointer)->Int32).self)(Int32(thepoint.x), Int32(size_y-1-Int(thepoint.y)), eventParams[idx]) }
	}
  }

  override func mouseDown(with event: NSEvent)  { mouse(with:event, index:4, type:0)  }
  override func rightMouseDown(with event: NSEvent)   {	mouse(with:event, index:4, type:0)  }
  override func otherMouseDown(with event: NSEvent)   {	mouse(with:event, index:4, type:0)  }

  override func mouseUp(with event: NSEvent)  { mouse(with:event, index:5, type:0)  }
  override func rightMouseUp(with event: NSEvent)   { mouse(with:event, index:5, type:0)  }
  override func otherMouseUp(with event: NSEvent)   { mouse(with:event, index:5, type:0)  }

  override func mouseMoved(with event: NSEvent)   { mouse(with:event, index:6, type:1)  }
  override func mouseDragged(with event: NSEvent)   { mouse(with:event, index:6, type:1)  }
  override func rightMouseDragged(with event: NSEvent)   { mouse(with:event, index:6, type:1)  }
  override func otherMouseDragged(with event: NSEvent)   { mouse(with:event, index:6, type:1)  }


  override func scrollWheel(with event: NSEvent)
  {
	var thepoint:NSPoint
	var button = 0;

	thepoint = event.locationInWindow
	if (event.deltaY > 0.2) { button = 4; }
	if (event.deltaY < -0.2) { button = 5; }
	if (event.deltaX > 0.2) { button = 6; }
	if (event.deltaX < -0.2) { button = 7; }
        if (button != 0 && eventFuncts[4] != nil)
        {
          _ = unsafeBitCast(eventFuncts[4],to:(@convention(c)(Int32, Int32, Int32, UnsafeRawPointer)->Int32).self)(Int32(button), Int32(thepoint.x), Int32(thepoint.y), eventParams[4])
        }
  } 


  override func flagsChanged(with event: NSEvent)
  {
	var flag:UInt32
	var the_key:Int32
	var val:UInt32

	flag = UInt32(event.modifierFlags.rawValue)
	val = (keyflag|flag)&(~(keyflag&flag))
	if (val == 0)
	    { return }   /// no change - can happen when loosing focus on special key pressed, then re-pressed later
         the_key = 1
	 while (((val >> (the_key-1)) & 0x01)==0)
	  { the_key += 1 }
	 if (flag > keyflag && eventFuncts[2] != nil)
	   { _ = unsafeBitCast(eventFuncts[2],to:(@convention(c)(Int32, UnsafeRawPointer)->Int32).self)(0xFF+the_key, eventParams[2]) }
	 if (flag < keyflag && eventFuncts[3] != nil)
	   { _ = unsafeBitCast(eventFuncts[3],to:(@convention(c)(Int32, UnsafeRawPointer)->Int32).self)(0xFF+the_key, eventParams[3]) }
	 keyflag = flag
  }

}


public class MlxWin
{
  var winE: WinEvent

  var device: MTLDevice
  var mview: MTKView
  var md: MTKVDelegate

  public init(device d:MTLDevice, width w:Int, height h:Int, title t:String)
  {
    let rect = CGRect(x: 100, y: 100, width: w, height: h)
    winE = WinEvent(frame: rect)

    device = d
    mview = MTKView(frame: rect, device:device)
    mview.clearColor = MTLClearColorMake(0, 0, 0, 0)
    mview.colorPixelFormat = .bgra8Unorm
    mview.isPaused = true
    mview.enableSetNeedsDisplay = false
    md = MTKVDelegate(view:mview, device:device)
    mview.delegate = md
    clearWin()

    winE.contentView = mview
    winE.title = t
    winE.makeKeyAndOrderFront(self)
  }

/// winEvent calls
  public func getWinEFrame() -> NSRect  { return winE.frame }
  public func getScreenFrame() -> NSRect { return winE.screen!.frame }
  public func getMouseLoc() -> NSPoint { return winE.mouseLocationOutsideOfEventStream }
  public func addHook(index idx:Int, fct fptr:UnsafeMutableRawPointer, param pptr:UnsafeMutableRawPointer)
  {  winE.addHook(index: idx, fct: fptr, param: pptr)  }
  public func setKeyRepeat(_ mode:Int)  { winE.setKeyRepeat(mode) }
  public func destroyWinE()  { winE.close() }

/// mtkviewdelegate calls
  public func clearWin()  {  md.clearWin() }
  public func pixelPut(_ x:Int32, _ y:Int32, _ color:UInt32)  {  md.pixelPut(x, y, color) }
  public func putImageScale(image img:MlxImg, x posx:Int32, y posy:Int32, dw dest_w:Int32, dh dest_h:Int32) { md.putImageScale(img, posx, posy, dest_w, dest_h) }
  public func putImage(image img:MlxImg, x posx:Int32, y posy:Int32) { md.putImage(img, posx, posy) }
  public func waitForGPU() { md.waitForGPU() }
  public func flushPixels() { md.flushPixels() }

}




let shaders = """
#include <metal_stdlib>
using namespace metal;

struct VertexIn {
    float4 position;
    float4 UV;
};
struct VertexOut {
    float4 position [[ position ]];
    float2 UV;
};
struct uniforms {
   packed_float2 winsize;
   packed_float2 size;
   packed_float2 pos;
};
vertex VertexOut basic_vertex_function(const device VertexIn *vertices [[ buffer(0) ]], constant uniforms& uni [[ buffer(1) ]],
uint vertexID [[ vertex_id ]])
{
    VertexOut vOut;
    /* vOut.position = vertices[vertexID].position; */
    float startx = (2.0*uni.pos.x)/(uni.winsize.x-1.0) - 1.0;
    float starty = (2.0*(uni.winsize.y-1.0-uni.pos.y))/(uni.winsize.y-1.0) - 1.0 - uni.size.y*2.0/uni.winsize.y;
    vOut.position = float4(startx+((vertices[vertexID].position.x + 1.0)*uni.size.x)/(uni.winsize.x),
    		    	   starty+((vertices[vertexID].position.y + 1.0)*uni.size.y)/(uni.winsize.y), 0.0, 1.0);
    vOut.UV = float2(vertices[vertexID].UV.x, vertices[vertexID].UV.y);
    return vOut;
}
fragment float4 basic_fragment_function(VertexOut vIn [[ stage_in ]], texture2d<float> texture [[ texture(0) ]])
{
    constexpr sampler textureSampler (mag_filter::linear, min_filter::linear);
    return texture.sample(textureSampler, vIn.UV);
    return float4(1.0, 0.0, 0.0, 1.0);
}
"""


class MTKVDelegate: NSObject, MTKViewDelegate
{
  var device: MTLDevice
  var mview: MTKView
  var commandQueue: MTLCommandQueue!
  var pipelineState: MTLRenderPipelineState!
/// 3 params to pipeline
  var vertexBuffer: MTLBuffer!
  var uniformBuffer: MTLBuffer!
  var uniform_data:UnsafeMutablePointer<Float>
  var texture: MTLTexture

  var pixel_image:MlxImg
  var pixel_count:Int

  var drawable_texture: MTLTexture

  var doClear = false

  var GPUdone = true

   init(view: MTKView, device: MTLDevice)
   {
    self.mview = view
    self.device = device

    commandQueue = device.makeCommandQueue()!

    /// vertex buffer & shaders stay the always the same.

    let lib = try! device.makeLibrary(source: shaders, options: nil)
    let vertexFunction = lib.makeFunction(name: "basic_vertex_function")
    let fragmentFunction = lib.makeFunction(name: "basic_fragment_function")
    let pipelineDesc = MTLRenderPipelineDescriptor()
    pipelineDesc.colorAttachments[0].pixelFormat = .bgra8Unorm

    pipelineDesc.colorAttachments[0].isBlendingEnabled = true
    pipelineDesc.colorAttachments[0].rgbBlendOperation = .add
    pipelineDesc.colorAttachments[0].alphaBlendOperation = .add
    pipelineDesc.colorAttachments[0].sourceRGBBlendFactor = .oneMinusSourceAlpha
    pipelineDesc.colorAttachments[0].sourceAlphaBlendFactor = .oneMinusSourceAlpha
    pipelineDesc.colorAttachments[0].destinationRGBBlendFactor = .sourceAlpha
    pipelineDesc.colorAttachments[0].destinationAlphaBlendFactor = .sourceAlpha

    pipelineDesc.vertexFunction = vertexFunction
    pipelineDesc.fragmentFunction = fragmentFunction
    pipelineState = try! device.makeRenderPipelineState(descriptor: pipelineDesc)

    let vertexData: [Float] = [
       -1.0, -1.0, 0.0, 1.0,  0.0, 1.0, 0.0, 0.0,
       -1.0, 1.0, 0.0, 1.0,   0.0, 0.0, 0.0, 0.0,
       1.0, -1.0, 0.0, 1.0,   1.0, 1.0, 0.0, 0.0,
       1.0, -1.0, 0.0, 1.0,   1.0, 1.0, 0.0, 0.0,
       -1.0, 1.0, 0.0, 1.0,   0.0, 0.0, 0.0, 0.0,
       1.0, 1.0, 0.0, 1.0,    1.0, 0.0, 0.0, 0.0  ]
    var dataSize = vertexData.count * MemoryLayout.size(ofValue: vertexData[0])
    vertexBuffer = device.makeBuffer(bytes: vertexData, length: dataSize, options: []) 

    let vrect = view.frame
    let uniformData: [Float] = [
    	Float(vrect.size.width), Float(vrect.size.height),
	1.0, 1.0, 0.0, 0.0  ]
    dataSize = uniformData.count * MemoryLayout.size(ofValue: uniformData[0])
    uniformBuffer = device.makeBuffer(bytes: uniformData, length: dataSize, options: [])
    uniform_data = (uniformBuffer.contents()).assumingMemoryBound(to:Float.self)

    drawable_texture = view.currentDrawable!.texture
    texture = drawable_texture

    pixel_image = MlxImg(d: device, w:Int(vrect.size.width), h:Int(vrect.size.height))
    for i in 0...(pixel_image.texture_height*pixel_image.texture_sizeline/4-1)
    {    pixel_image.texture_data[i] = UInt32(0xFF000000) }
    pixel_count = 0

    super.init()
   }


  func clearWin()
  {
	doClear = true
	mview.draw()
  }

  func pixelPut(_ x:Int32, _ y:Int32, _ color:UInt32)
  {
	pixel_image.texture_data[Int(y)*pixel_image.texture_sizeline/4+Int(x)] = color
	pixel_count += 1
	if (pixel_count >= 200000)
	{
		flushPixels()
	}
  }

  func flushPixels()
  {
	if (pixel_count > 0)
	{
	  self.putImage(pixel_image, 0, 0)
	  for i in 0...pixel_image.texture_height*pixel_image.texture_sizeline/4-1
	    {    pixel_image.texture_data[i] = UInt32(0xFF000000) }
	  pixel_count = 0
	}
  }


  func putImage(_ img:MlxImg, _ x:Int32, _ y:Int32)
  {
	putImageScale(img, x, y, Int32(img.texture_width), Int32(img.texture_height))
  }

  func putImageScale(_ img:MlxImg, _ x:Int32, _ y:Int32, _ dest_w:Int32, _ dest_h:Int32)
  {
	uniform_data[2] = Float(dest_w)
	uniform_data[3] = Float(dest_h)
	uniform_data[4] = Float(x)
	uniform_data[5] = Float(y)
	texture = img.texture
	mview.draw()
  }

  public func waitForGPU()
  {
	while (GPUdone == false) { }
  }

  // 2 delegate MTKView functs

  func mtkView(_ view: MTKView, drawableSizeWillChange size: CGSize)
  {

  }

  func draw(in view: MTKView)
  {
	let commandBuffer = commandQueue.makeCommandBuffer()!
	if let renderPassDescriptor = view.currentRenderPassDescriptor
	 {
		renderPassDescriptor.colorAttachments[0].storeAction = .store
		if (doClear)
		{
		  renderPassDescriptor.colorAttachments[0].loadAction = .clear
                  renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColor(red: 0.0, green: 0.0, blue: 0.0, alpha:0.0)
		  let commandEncoder = commandBuffer.makeRenderCommandEncoder(descriptor: renderPassDescriptor)!
		  commandEncoder.endEncoding()
		  doClear = false
		}
		else
		{

/// first draw back prev buffer
		  let commandBEncoder = commandBuffer.makeBlitCommandEncoder()!
	 	  commandBEncoder.copy(from:drawable_texture, sourceSlice:0, sourceLevel:0, sourceOrigin: MTLOriginMake(0,0,0), sourceSize: MTLSizeMake(drawable_texture.width, drawable_texture.height, 1),  to:view.currentDrawable!.texture, destinationSlice:0, destinationLevel:0, destinationOrigin: MTLOriginMake(0,0,0))
	 	  commandBEncoder.endEncoding()


/// then draw new image
		  renderPassDescriptor.colorAttachments[0].loadAction = .load
		  let commandEncoder = commandBuffer.makeRenderCommandEncoder(descriptor: renderPassDescriptor)!
		  commandEncoder.setRenderPipelineState(pipelineState)
		  commandEncoder.setVertexBuffer(vertexBuffer, offset: 0, index: 0)
		  commandEncoder.setVertexBuffer(uniformBuffer, offset: 0, index: 1)
		  commandEncoder.setFragmentTexture(texture, index: 0)
		  commandEncoder.drawPrimitives(type: .triangleStrip, vertexStart: 0, vertexCount: 6, instanceCount:2)
		  commandEncoder.endEncoding()
                }	
         }
	while (GPUdone == false) { }
	GPUdone = false
	commandBuffer.addCompletedHandler { cb in self.GPUdone = true }
	commandBuffer.present(view.currentDrawable!)
        commandBuffer.commit()

///	commandBuffer.waitUntilCompleted()

	drawable_texture = view.currentDrawable!.texture
  }

}

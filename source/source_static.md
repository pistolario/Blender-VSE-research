# About source static

## Main structures

The main structure is *Sequence*, and it is located in DNA_sequence_types.h

```C
/**
 * The sequence structure is the basic struct used by any strip.
 * each of the strips uses a different sequence structure.
 *
 * \warning The first part identical to ID (for use in ipo's)
 * the comment above is historic, probably we can drop the ID compatibility,
 * but take care making this change.
 *
 * \warning This is really a 'Strip' in the UI!, name is highly confusing.
 */
typedef struct Sequence {
  struct Sequence *next, *prev;
  /** Tmp var for copying, and tagging for linked selection. */
  void *tmp;
  /** Needed (to be like ipo), else it will raise libdata warnings, this should never be used. */
  void *lib;
  /** SEQ_NAME_MAXSTR - name, set by default and needs to be unique, for RNA paths. */
  char name[64];

  /** Flags bitmap (see below) and the type of sequence. */
  int flag, type;
  /** The length of the contents of this strip - before handles are applied. */
  int len;
  /**
   * Start frame of contents of strip in absolute frame coordinates.
   * For metastrips start of first strip startdisp.
   */
  int start;
  /**
   * Frames after the first frame where display starts,
   * frames before the last frame where display ends.
   */
  int startofs, endofs;
  /**
   * Frames that use the first frame before data begins,
   * frames that use the last frame after data ends.
   */
  int startstill, endstill;
  /** Machine: the strip channel */
  int machine;
  int _pad3;
  /** Starting and ending points of the strip in the sequence. */
  int startdisp, enddisp;
  float sat;
  float mul;
  float _pad;

  short anim_preseek; /* UNUSED. */
  /** Streamindex for movie or sound files with several streams. */
  short streamindex;
  /** For multicam source selection. */
  int multicam_source;
  /** MOVIECLIP render flags. */
  int clip_flag;

  Strip *strip;

  /** Old animation system, deprecated for 2.5. */
  struct Ipo *ipo DNA_DEPRECATED;

  /** these ID vars should never be NULL but can be when linked libs fail to load,
   * so check on access */
  struct Scene *scene;
  /** Override scene camera. */
  struct Object *scene_camera;
  /** For MOVIECLIP strips. */
  struct MovieClip *clip;
  /** For MASK strips. */
  struct Mask *mask;
  /** For MOVIE strips. */
  ListBase anims;

  float effect_fader;
  /* DEPRECATED, only used for versioning. */
  float speed_fader;

  /* pointers for effects: */
  struct Sequence *seq1, *seq2, *seq3;

  /** List of strips for metastrips. */
  ListBase seqbase;
  ListBase channels; /* SeqTimelineChannel */

  /** The linked "bSound" object. */
  struct bSound *sound;
  void *scene_sound;
  float volume;

  /** Pitch (-0.1..10), pan -2..2. */
  float pitch, pan;
  float strobe;

  /** Struct pointer for effect settings. */
  void *effectdata;

  /** Only use part of animation file. */
  int anim_startofs;
  /** Is subtle different to startofs / endofs. */
  int anim_endofs;

  int blend_mode;
  float blend_opacity;

  /* Tag color showed if `SEQ_TIMELINE_SHOW_STRIP_COLOR_TAG` is set. */
  int8_t color_tag;

  char alpha_mode;
  char _pad4[2];

  int cache_flag;

  /* is sfra needed anymore? - it looks like its only used in one place */
  /** Starting frame according to the timeline of the scene. */
  int sfra;

  /* Multiview */
  char views_format;
  char _pad1[3];
  struct Stereo3dFormat *stereo3d_format;

  struct IDProperty *prop;

  /* modifiers */
  ListBase modifiers;

  SequenceRuntime runtime;

  ListBase soundeqs;
} Sequence;

```


# RNA related

The first stop is **source/blender/makesrna/intern/rna_sequencer.c**.

There, it is defined all the public structures of the VSE and *strips* (called
*sequence* in the source code.

```C

void RNA_def_sequencer(BlenderRNA *brna)
{
  rna_def_color_balance(brna);

  rna_def_strip_element(brna);
  rna_def_strip_proxy(brna);
  rna_def_strip_color_balance(brna);
  rna_def_strip_crop(brna);
  rna_def_strip_transform(brna);

  rna_def_sequence(brna);
  rna_def_editor(brna);
  rna_def_channel(brna);

  rna_def_image(brna);
  rna_def_meta(brna);
  rna_def_scene(brna);
  rna_def_movie(brna);
  rna_def_movieclip(brna);
  rna_def_mask(brna);
  rna_def_sound(brna);
  rna_def_effect(brna);
  rna_def_effects(brna);
  rna_def_modifiers(brna);
}

```

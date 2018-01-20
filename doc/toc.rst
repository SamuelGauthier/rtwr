=================
Table of contents
=================

.. Based on "The Mayfield Handbook of Technical & Scientific Writing"

Project report containing a vision for the bachelor thesis.

.. Or is it a project article? Article or Report?

Title: Real-Time Rendering Large Bodies of Realistic Water

.. Rendering in Real-Time Large Bodies of Realistic Water
   Rendering Large Bodies of Realistic Water in Real-Time
   Real-Time Rendering: Rendering Large Bodies of Realistic Water
   Real-Time Rendering Realistic Large Bodies of Water
   Realistic, Real-Time Rendering of Large Bodies of Water
   Real-Time Water Rendering: Analysis of Available Methods for Large Bodies of
   Water Observed at Aerial View
   Real-Time Water Rendering: Realistic Large Bodies of Water

Abstract
1. Introduction
2. Background -> Water Models (or: A History of Water Models)
   1. Navier Stokes Equations
   2. Eulerian framework
   3. Lagrangian framework
3. Methods -> The Simple Gerstner Wave Approach
   Gerstner Waves
   State of the art in production
   Embedding solution into a custom application
4. Results -> Performance and Visual Results
   Custom Application with Gerstner Waves
5. Discussion
6. Conclusion


.. What are the desired effects? What are the things done today? What are the
   existing shaders in Unity and Unreal? History of water shaders
   Where should the literature research be placed?

Problem     Render large bodies of water, and include all the visual details.
            In a realistic way.

Background  Navier stokes, Different level of water depth, Spatial, Spectral
            domain, eulerian, lagrangian frameworks, talk about their visual
            accuracy, SLProject, 0 a.d.

Method      Simple approach Gerstner and GPU fragment, vertex computations.
            OpenGL setup of custom application, SLProject not working, 0 a.d.
            overkill.

Results     Bad performance, not optimized, visually not that conviencing
            because of bad parameters and which have to be guessed, brdf and
            fresnel problem

Analysis    Failed attempt, in future use projected grid as in many productions,
            integrating in 0 a.d. will be difficult because rendering time is
            unknown, targeted devices may not support it?

            .. Even if the used method is not good, the result is important
            because it showed the limitation of doing expensive computations


Abstract
--------

An abstract is a brief summarizing statement, usually between 75 and 150 words
long. It gives the reader a synopsis of the problem, method, results, and
conclusions of your document. The abstract takes the form of a paragraph,
usually with 5-10 sentences. It appears at the top of a journal article, just
under the title, or on the page following the title page of a report. In the
latter instance, the abstract appears on a page by itself.


An abstract includes these elements:

1. Problem. Note the key topic or problem of your document.
2. Method. State your main approach to solving the problem.
3. Results. Provide one or two important results.
4. Conclusion. Note your main conclusion.


Introduction
------------

The introduction to your document should lead your readers into your paper and
give them an idea of what to expect (also see Forecasting). It should not be
simply a restatement of the abstract even though it will contain some of the
same material.

Introductions often do the following:

- State the subject of your document as clearly as possible
- Define the problem you are addressing, your approach to the problem, and why
  this problem is important
- State the purpose of your document
- Define the scope of your document
- Provide necessary and relevant background information

Because the introduction leads your reader into your document, try to begin with
a general statement about the topic before moving on to specific issues. This
strategy will help make the topic accessible to your readers, especially those
who are not specialists in the field.

Background
----------

Provide enough information in a technical document to allow your reader to
understand the specific problem being addressed and to provide a context for
your own document. This background information may include (1) a historical
summary of the problem being addressed; (2) a brief summary of previous work on
the topic, including, if appropriate, relevant theory; and (3) the specific
reasons the document is being written.

Theory
------

In long and fairly complex reports and articles, especially theoretical and
experimental reports where the purpose of the document is to apply, verify, or
illustrate one or more theories, include a separate section presenting relevant
theoretical formulae and the techniques by which any experimental results are
predicted. When introducing equations, be sure to define all symbols used in
them.

Results
-------

In the results section of a report, describe all appropriate information
produced by the research procedures. Simply present data and estimates of their
accuracy. Save the explanation and interpretation of these findings for the
discussion section, which usually follows the results section. In short
documents, however, the results and discussion sections may be combined into a
single section.

Results sections make extensive use of graphs and figures to present data
effectively. Order information by its importance to your audience's purpose in
reading the document. State all significant findings in the text, referring to
tables and graphs displaying all significant data. If the study has produced a
large amount of raw data, do not present all of it in the results section.
Instead, present only the information most appropriate to your audience's
purpose in reading the document, summarizing other key information in graphs and
figures. If appropriate, include your raw data in an appendix, referring to them
within your text.

Discussion
----------

Explain in the discussion section of your document information presented in the
results section, commenting on significant data produced by the study. In
writing a discussion section, keep the following points in mind.

- Identify significant patterns in the data and relationships between variables.
  Offer tentative explanations for these patterns and relationships.
- Compare the actual data produced with any predictions or questions posed in
  the introduction or theory section of the document.
- If any of the results differ from the expected results, offer possible
  explanations for the discrepancies. Present the most probable explanations
  first and the least probable last.
- Consider how well the data answer any questions posed in the document's
  introduction. Do the results answer the questions completely? If not, explain
  what questions still need to be addressed and give possible explanations why
  the results may be inconclusive.
- Qualify the scope of your explanations, discussing in what cases your
  explanations apply and in what cases they may not.
- Organize your material in order of importance to your reader's purpose in
  using the document.

Conclusion
----------

This part of the document should summarize all essential information necessary
for your audience's purpose. In your conclusion:

- Relate your findings to the general problem and any specific objectives posed
  in your introduction.
- Summarize clearly what the report does and does not demonstrate.
- Include specific recommendations for action or for further research. Sometimes
  these recommendations will constitute a separate section of a document.

--------------------------------------------------------------------------------

Project Report
~~~~~~~~~~~~~~

You should prepare a project report, using a word processor. The report should
primarily document the work done. It should contain two parts.

1. A main part, explaining the problem and your solution. About the size of an
   IEEE transactions paper (i.e. maximum 10 pages in two columns and 11 point
   font).
   A. What is the problem you had to solve ? why it is a problem ? why would any
      one care about solving it ?
   B. Describe your solution. Explain the main features, the ones you believe
      are most valuable.
   C. List your achievements, give their nature, quality and quantity.
      Distinguish your contribution from what others did before. For example: I
      designed an ns model of the VP-TFMCC protocol, 2500 lines of simple code,
      300 lines of high value code. Debugging took 2 weeks.
   D. What skills did you exercise, what skills did you have to acquire for the
      project
   E. Report on the major events of the project, including unexpected
      difficulties.
   F. Provide a self-assessment (where did you succeed most, where did you fail)

2. An appendix with supporting material:
   A. Give the background information that is needed to understand and
      appreciate your work.
   B. Give only this background information (your report is a project
      achievement report; it should explain very clearly what you did, but does
      not have to be a tutorial on a general topic.)
   C. Details of source code, simulation results, measurement campaigns.
   D. Details about project events.

--------------------------------------------------------------------------------

Document purpose
================

Sections in Document
--------------------

Front Matter
- Title page
- Abstract
- TOC

Body:
- Introduction
- **Background**
- **Theory**
- Design criteria
- **Material and apparatus**
- Procedure
- Workplan
- **Results**
- Discussion
- Conclusion
- Recommendation

End matter:
- References
- Appendixes

Explicit purpose
----------------

Goal: provide information
This document will discuss the various methods that can be used in a game
engine to render water in real time.

.. Focus on one type of game: real time strategy. Also outline vision for
   bachelor thesis

Implicit purpose
----------------

- Establish a relastionship
- Create trust en establish credibility
- Document actions

Statement of Objective
----------------------

State the document's objective at the beginning


Problem statement
=================

Problem statements often have three elements:

1. the problem itself, stated clearly and with enough contextual detail to
   establish why it is important;
2. the method of solving the problem, often stated as a claim or a working
   thesis;
3. the purpose, statement of objective and scope of the document the writer is
   preparing.

These elements should be brief so that the reader does not get lost.

.. Bird's eye view?

Real-time water rendering for large masses of water observed at aerial view.


Audience
========

Audience type: experts

- If your audience includes general experts, provide sufficient background
  information and define any terms that they might be unfamiliar with.
- Do not just present a concept to an expert. Also explain its parts and
  processes in detail.

Forecasting
===========

Present the whole before the parts. One of the common problems in reading
science and engineering materials is that of trying to understand the context of
the discussion. Give your reader a general view of where you are going before
you plunge into the details. This principle applies to the introductions of
documents, as well as to the openings of document sections.

Drafting a Technical Document
=============================

- Writing can generate new ideas. If you discover potentially relevant new ideas
  or approaches, include them even if they are not in your outline. You can
  revise your outline when you edit for organization.
- The main purpose of a first draft is to sketch out ideas in writing.
  Consequently, fixing specific problems in sentences, words, grammar, spelling,
  usage, or mechanics when writing a first draft can be distracting and can
  hinder the development of important and interesting ideas. Many writers just
  mark these problems when writing a first draft and then address them when they
  edit for grammar, style, and usage.
- You may find yourself needing to locate or develop additional data or to
  confirm already exisiting data. Marginal notes or comments in the text (e.g.,
  "add median response time," "need figures," or "check maximum values") allow
  you to keep your ideas flowing.
- You do not need to write the document in the order of your outline. Many
  writers, for example, find it useful to write the introduction and the
  conclusion of a document last.

--------------------------------------------------------------------------------

Voice
-----

Use the passive voice to express actions in which the agent is arbitrary, not
known, or not important. Otherwise, use the active voice.

Passive vs Active:

Use the active voice whenever the passive voice is not appropriate. Active verbs
make for concise prose; sentences with passive verbs use more words. Moreover,
passive verbs deemphasize or even eliminate mention of the performer of the
action conveyed by the verb.

--------------------------------------------------------------------------------

The General Rules for Title Case
--------------------------------
Style guide similarities:

- In all three styles, always capitalize the first and last word of any title.
    + How to Land Your Dream Job
- In all three styles, capitalize nouns, pronouns, verbs, adjectives, and adverbs.
    + Visiting Beautiful Ruins (noun)
    + As She Ran Away (pronoun)
    + The Importance of Learning Fast (verb)
    + The Poky Little Puppy (adjective)
    + She Quietly Waits (adverb)
- In all three styles, do not capitalize articles, prepositions, or coordinating
  conjunctions.
    + To Catch a Thief (article)
    + One Year in Paris (preposition)
    + Magic and Daybreak (coordinating conjunction)

--------------------------------------------------------------------------------

Document Checklist
------------------

1. Coverage and Organization
   - Is the problem defined clearly and placed in context?
   - Are all the elements (title page, executive summary, introduction, etc.)
     included as required by a standard format?
   - Is the material addressed to a specific audience in organization, coverage,
     and difficulty?
   - Are sections labeled with descriptive subject headings?
   - Are graphics, illustrations, and tables used to present key concepts,
     apparatus, and data?

2. Expression
   - Paragraphs
        + Are paragraphs used effectively to organize the material?
        + Do the paragraphs have clear topic sentences?
        + Are the paragraphs coherent?
   
   - Sentences
        + Are sentences free of deadwood?
        + Is the sentence structure clear?
        + Do the sentences use frequent active verbs?
        + Has the material been read for grammatical errors?
   
   - Words
        + Are words and terms used accurately?
        + Is there effective descriptive detail?
        + Has the spelling been checked?

3. Mechanics
   - Do figures and tables have descriptive captions and accurate labels?
   - Are the following items correctly and consistently numbered?
        + Pages
        + Sections
        + Figures
        + Tables
        + Equations
        + References
        + Appendixes
     
   - Has the document been proofread for accurate punctuation and possible
     typos?
   - Have all citations, references and uses of material been properly
     identified and credited?

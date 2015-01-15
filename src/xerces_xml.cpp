/*
 * reference from: http://www.yolinux.com/TUTORIALS/XML-Xerces-C.html
 * 
 * compile environment:  Gentoo
 * library from package: dev-libs/xerces-c
 * 
 * compile comand:
 * $ g++ -ggdb -Wall xerces_xml.cpp -lxerces-c 
 * $ ./a.out
 *
 */

#include <iostream>
#ifndef XML_PARSER_HPP
#define XML_PARSER_HPP
/**
 *  @file
 *  Class "GetConfig" provides the functions to read the XML data.
 *  @version 1.0
 */
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

#include <string>
#include <stdexcept>

// Error codes

enum {
   ERROR_ARGS = 1, 
   ERROR_XERCES_INIT,
   ERROR_PARSE,
   ERROR_EMPTY_DOCUMENT
};

class GetConfig
{
public:
   GetConfig();
  ~GetConfig();
   void readConfigFile(std::string&) throw(std::runtime_error);
 
   char *getOptionA() { return m_OptionA; };
   char *getOptionB() { return m_OptionB; };

private:
   xercesc::XercesDOMParser *m_ConfigFileParser;
   char* m_OptionA;
   char* m_OptionB;

   // Internal class use only. Hold Xerces data in UTF-16 SMLCh type.

   XMLCh* TAG_root;

   XMLCh* TAG_ApplicationSettings;
   XMLCh* ATTR_OptionA;
   XMLCh* ATTR_OptionB;
};
#endif

#include <string>
#include <sstream>
#include <stdexcept>
#include <list>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>





using namespace xercesc;
using namespace std;

/**
 *  Constructor initializes xerces-C libraries.
 *  The XML tags and attributes which we seek are defined.
 *  The xerces-C DOM parser infrastructure is initialized.
 */

GetConfig::GetConfig()
{
   try
   {
      XMLPlatformUtils::Initialize();  // Initialize Xerces infrastructure
   }
   catch( XMLException& e )
   {
      char* message = XMLString::transcode( e.getMessage() );
      cerr << "XML toolkit initialization error: " << message << endl;
      XMLString::release( &message );
      // throw exception here to return ERROR_XERCES_INIT
   }

   // Tags and attributes used in XML file.
   // Can't call transcode till after Xerces Initialize()
   TAG_root        = XMLString::transcode("note");
   TAG_ApplicationSettings = XMLString::transcode("key1");
   ATTR_OptionA = XMLString::transcode("o1");
   ATTR_OptionB = XMLString::transcode("o2");

   m_ConfigFileParser = new XercesDOMParser;
}

/**
 *  Class destructor frees memory used to hold the XML tag and 
 *  attribute definitions. It als terminates use of the xerces-C
 *  framework.
 */

GetConfig::~GetConfig()
{
   // Free memory

   delete m_ConfigFileParser;
   if(m_OptionA)   XMLString::release( &m_OptionA );
   if(m_OptionB)   XMLString::release( &m_OptionB );

   try
   {
      XMLString::release( &TAG_root );

      XMLString::release( &TAG_ApplicationSettings );
      XMLString::release( &ATTR_OptionA );
      XMLString::release( &ATTR_OptionB );
   }
   catch( ... )
   {
      cerr << "Unknown exception encountered in TagNamesdtor" << endl;
   }

   // Terminate Xerces

   try
   {
      XMLPlatformUtils::Terminate();  // Terminate after release of memory
   }
   catch( xercesc::XMLException& e )
   {
      char* message = xercesc::XMLString::transcode( e.getMessage() );

      cerr << "XML ttolkit teardown error: " << message << endl;
      XMLString::release( &message );
   }
}

/**
 *  This function:
 *  - Tests the access and availability of the XML configuration file.
 *  - Configures the xerces-c DOM parser.
 *  - Reads and extracts the pertinent information from the XML config file.
 *
 *  @param in configFile The text string name of the HLA configuration file.
 */

void GetConfig::readConfigFile(string& configFile)
        throw( std::runtime_error )
{
   // Test to see if the file is ok.

   struct stat fileStatus;

   errno = 0;
   if(stat(configFile.c_str(), &fileStatus) == -1) // ==0 ok; ==-1 error
   {
       if( errno == ENOENT )      // errno declared by include file errno.h
          throw ( std::runtime_error("Path file_name does not exist, or path is an empty string.") );
       else if( errno == ENOTDIR )
          throw ( std::runtime_error("A component of the path is not a directory."));
       else if( errno == ELOOP )
          throw ( std::runtime_error("Too many symbolic links encountered while traversing the path."));
       else if( errno == EACCES )
          throw ( std::runtime_error("Permission denied."));
       else if( errno == ENAMETOOLONG )
          throw ( std::runtime_error("File can not be read\n"));
   }

   // Configure DOM parser.

   m_ConfigFileParser->setValidationScheme( XercesDOMParser::Val_Never );
   m_ConfigFileParser->setDoNamespaces( false );
   m_ConfigFileParser->setDoSchema( false );
   m_ConfigFileParser->setLoadExternalDTD( false );

   try
   {

      // 1. parsing root
      m_ConfigFileParser->parse( configFile.c_str() );
      // no need to free this pointer - owned by the parent parser object
      DOMDocument* xmlDoc = m_ConfigFileParser->getDocument();
      // Get the top-level element: NAme is "root". No attributes for "root"
      DOMElement* elementRoot = xmlDoc->getDocumentElement();
      if( !elementRoot ) throw(std::runtime_error( "empty XML document" ));


      // 2. count node
      // Parse XML file for tags of interest: "ApplicationSettings"
      // Look one level nested within "root". (child of root)
      DOMNodeList*      children = elementRoot->getChildNodes();
      const  XMLSize_t nodeCount = children->getLength();


      // 3. parsing target nodes
      // For all nodes, children of "root" in the XML tree.
      for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
      {
         DOMNode* currentNode = children->item(xx);
         if( currentNode->getNodeType() &&  // true is not NULL
             currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
         {
            // Found node which is an Element. Re-cast node as element
            DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
            if( XMLString::equals(currentElement->getTagName(), TAG_ApplicationSettings))
            {
               // Already tested node as type element and of name "ApplicationSettings".
               // Read attributes of element "ApplicationSettings".
               const XMLCh* xmlch_OptionA = currentElement->getAttribute(ATTR_OptionA);
               m_OptionA = XMLString::transcode(xmlch_OptionA);

               const XMLCh* xmlch_OptionB = currentElement->getAttribute(ATTR_OptionB);
               m_OptionB = XMLString::transcode(xmlch_OptionB);

               break;  // Data found. No need to look at other elements in tree.
            }
         }
      }
   }
   catch( xercesc::XMLException& e )
   {
      char* message = xercesc::XMLString::transcode( e.getMessage() );
      ostringstream errBuf;
      errBuf << "Error parsing file: " << message << flush;
      XMLString::release( &message );
   }
}


int main(){
    using std::cout;
    using std::endl;
    using std::string;

    string configFile="xerces_xml.xml";
    GetConfig appConfig;

    appConfig.readConfigFile(configFile);


    //cout << "hello world" << endl;
    cout << "key1: " << appConfig.getOptionA() << endl;
    cout << "key2: " << appConfig.getOptionB() << endl;

    return 0;
}



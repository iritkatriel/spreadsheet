//
//  cell.hpp
//  spreadsheet
//
//  Created by Irit Katriel on 01/08/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "streamulus.h"

namespace spreadsheet {
    
    template<typename T>
    class Cell
    {
    public:
        
        typedef boost::shared_ptr<streamulus::StropStreamProducer<T> > ptr_type;
        typedef const boost::proto::literal<ptr_type> type;    
        typedef type expr_type;

        Cell()
            : mOutStream(boost::make_shared<streamulus::DataSource<T> >("tmp", false))
        {
            SetEngine(NULL, "");
        }
        
        Cell(streamulus::Streamulus* streamulus_engine, const std::string& name)
            : mOutStream(boost::make_shared<streamulus::DataSource<T> >("tmp", false))
        {
            SetEngine(streamulus_engine, name);
        }
        
        void SetEngine(streamulus::Streamulus* streamulus_engine, const std::string& name)
        {
            mStreamulusEngine = streamulus_engine;
            mName = name;
        }
                
        expr_type operator()() const
        {
            return boost::proto::lit(mOutStream);
        }
                
        T Value()
        {
            assert(IsValid());
            return *mValue;
        }
        
        template<typename Expr>
        void Set(const Expr& expr)
        {
            using streamulus::Streamify;
            
            if (mSubscription)
                mStreamulusEngine->UnSubscribe(*mSubscription);
            
            SetCellValue set_cell_value(this);
            mSubscription.reset(mStreamulusEngine->Subscribe(Streamify(set_cell_value)(expr))); 
        }

    private:
                
        bool IsValid()
        {
            return mSubscription && mValue;
        }
        
        void SetValue(const T& value)
        {
            mValue = value;
            InputStreamPut(mOutStream,value);
        }
        
        
        struct SetCellValue
        {
        public:
            SetCellValue(Cell* cell)
                :mCell(cell)
            {
            }
            
            template<class Sig> 
            struct result 
            {
                typedef T type; 
            };
            
            typename result<SetCellValue>::type
            operator()(const T& value)
            {
                // std::cout << mCell->mName << " <-- " << value << std::endl;
                mCell->SetValue(value);
                return value;
            }
            
        private:
            Cell* mCell;
        };
        

        streamulus::Streamulus* mStreamulusEngine; // No ownership. Do not delete.
        std::string mName;
        boost::optional<expr_type> mSubscription;
        boost::shared_ptr<streamulus::DataSource<T> > mOutStream;
        boost::optional<T> mValue;
    };
    
} // ns spreadsheet


